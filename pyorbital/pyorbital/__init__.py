# import os, yaml, re, sys
# from pathlib import Path
# import click

from invoke import Program, Collection, Config
from pyorbital import tasks


class OrbitalConfig(Config):
    prefix = 'orbital'


program = Program(
    config_class=OrbitalConfig,
    namespace=Collection.from_module(tasks),
    version='0.1.0'
)
