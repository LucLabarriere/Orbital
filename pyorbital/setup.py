# setup.py
import setuptools

setuptools.setup(
    name="pyorbital",
    packages=setuptools.find_packages(),
    install_requires=[
        "invoke",
        "pyyaml",
        "click"
    ],
    entry_points={
        "console_scripts": [
            "orb = pyorbital:program.run",
        ]
    },
)
