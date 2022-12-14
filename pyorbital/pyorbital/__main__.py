import argparse, os, yaml, re, sys
from pathlib import Path

if __name__ == '__main__':
    current_dir = str(Path(__file__).parent)
    p = argparse.ArgumentParser(description='pyorbital program')
    conf = yaml.load(open(current_dir + '/../config.yaml', 'r'), Loader=yaml.Loader)
    orbital_source_path = current_dir + '/../' + conf['OrbitalSrcPath']

    sub_parsers = p.add_subparsers(dest='command')

    p_gen_script = sub_parsers.add_parser('gen_script')
    p_gen_script.add_argument('script_name', help='The name of the script', type=str)

    args = p.parse_args()

    if args.command == 'gen_script':
        h_output_path = f"{orbital_source_path}/OrbitalScripts/include/OrbitalScripts/{args.script_name}.h"
        cpp_output_path = f"{orbital_source_path}/OrbitalScripts/src/{args.script_name}.cpp"

        if os.path.exists(h_output_path) or os.path.exists(cpp_output_path):
            sys.exit(f"Error, {h_output_path} or {cpp_output_path} exist")

        with open(current_dir + '/script_template.h', 'r') as f:
                script_content_h = f.read().format(script_name=args.script_name)
        with open(current_dir + '/script_template.cpp', 'r') as f:
                script_content_cpp = f.read().format(script_name=args.script_name)

        with open(h_output_path, 'w') as f:
            f.write(script_content_h)
        with open(cpp_output_path, 'w') as f:
            f.write(script_content_cpp)

        print(f"The script was created: {args.script_name}")




