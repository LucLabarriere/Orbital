from invoke import task, Config
import os
import yaml


def check_config(reference, current) -> bool:
    valid = True

    for k in reference.keys():
        # If the reference key is not present in current config, incorrect
        if k not in current.keys():
            valid = False
            break

        # If the reference value is of a different type than the current value, incorrect
        elif type(reference[k]) != type(current[k]):
            valid = False
            break

        # If the value is a dict, rerun chec_config
        elif type(reference[k]) == type({}):
            valid = check_config(reference[k], current[k])

            if not valid:
                break

    return valid


def init_config_file() -> Config:
    config_file_path = 'orbital.yaml'
    reference = {
        'configure': {
            'c_compiler': '',
            'cxx_compiler': '',
            'source_dir': '.',
            'build_dir': './build',
            'generator': 'Ninja',
            'vcpkg_install': True,
        },
        'build': {'config': 'Debug'},
        'run': {'executable': 'FPSDemo'},
    }

    valid = os.path.exists(config_file_path)

    if not valid:
        print(f"{config_file_path} does not exist. Creating it")
        yaml.dump(reference, open(config_file_path, 'w'))
        valid = True

    else:
        current = yaml.load(open(config_file_path, 'r'), Loader=yaml.Loader)
        valid = check_config(reference, current)

    if not valid:
        print(f"{config_file_path} corrupted. Re-creating it")
        yaml.dump(reference, open(config_file_path, 'w'))

    return Config(yaml.load(open(config_file_path, 'r'), Loader=yaml.Loader))


@task
def configure(invoke_yaml):
    print("Configuring project using invoke.yaml config file")
    cmd_run = invoke_yaml.run

    # Gathering VCPKG
    cmd_run('git submodule init')
    cmd_run('git submodule update')

    # Checking invoke.yaml file
    invoke_yaml = init_config_file()
    c = invoke_yaml['configure']

    toolchain_path = f"{c.source_dir}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"

    cmd = f"cmake {c.source_dir} -B {c.build_dir} \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G \"{c.generator}\" \
    -DCMAKE_TOOLCHAIN_FILE={toolchain_path}"

    if c.c_compiler != "":
        cmd += f" -DCMAKE_C_COMPILER={c.c_compiler}"

    if c.cxx_compiler != "":
        cmd += f" -DCMAKE_CXX_COMPILER={c.cxx_compiler}"

    cmd += f" -DVCPKG_MANIFEST_INSTALL={'ON' if c.vcpkg_install else 'OFF'}"
    cmd += f" -DCMAKE_BUILD_TYPE={invoke_yaml.build.config.upper()}"

    cmd_run(cmd)


@task
def build(invoke_yaml):
    cmd_run = invoke_yaml.run

    # Checking invoke.yaml file
    invoke_yaml = init_config_file()
    c = invoke_yaml['build']

    print(f"Build project in {c.config} mode")
    cmd = f"cmake --build {invoke_yaml.configure.build_dir} --config={c.config}"

    cmd_run(cmd)


@task(default=True)
def run(invoke_yaml):
    cmd_run = invoke_yaml.run

    # Checking invoke.yaml file
    invoke_yaml = init_config_file()
    src = invoke_yaml.configure.source_dir
    exe = invoke_yaml.run.executable
    config = invoke_yaml.build.config

    executable_path = f"{src}/bin/{exe}"

    # For non Multi-Config generators (such as Unix Makefile)
    if not os.path.exists(executable_path):
        executable_path = f"{src}/bin/{config}/{exe}"

        # For Multi-Config generators (such as "Ninja Multi-Config" or "MSVC")
        if not os.path.exists(executable_path):
            print(
                f"Neither \"{f'{src}/bin/{exe}'}\" nor \"{f'{src}/bin/{config}/{exe}'}\" exist")
            print("Did you build the program ?")
            return

    print(f"Running executable {executable_path}")
    result = cmd_run(executable_path)
    print(f"The program terminated with return code: {result.exited}")
