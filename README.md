# markdown-inheritance

A pandoc buildsystem that uses default.yaml inheritance to form metadata hierachies

TODO: make it so that the script can do inplace initialisation.

## Usage

- Add `pandoc.sh` to your `PATH`

- Run `pandoc.sh init` in an empty directory use `--help` for more options.

### Creating subprojects

`pandoc.sh create-subproject`

## Runtime dependecies

- a container runner - podman

  uses container image `pandoc/extra`


## Bundling a new pandoc.sh script

### Build-time dependecies

`a c compiler, make`

### Bundling

cd into scripts and run `make pandoc.sh` which will build `scripts/pandoc.sh` copy this script the root of your repo or `PATH`
