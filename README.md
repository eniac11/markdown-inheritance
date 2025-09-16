# markdown-inheritance

A pandoc buildsystem that uses default.yaml inheritance to form metadata hierachies

TODO: make it so that the script can do inplace initialisation.

## Usage

- Add `pandoc.sh` to your `PATH`

- Run `pandoc.sh init` in an empty directory use `--help` for more options.

### Creating subprojects

`pandoc.sh create-subproject`

### Building a project


> [!NOTE]
>
> why `/data`
>
> The reason for `/data/` is when pandoc is run it is run from a container with
> the folder that contains `pandoc.sh` mounted into `/data` therefore it is
>  neccesary to have `pandoc.sh` copied into the root of the repo.

> [!TIP]
>
> `--defaults` can be replace with `-d`
>
> `--to <format>` can be replace with `-t <format>`

- Run `pandoc.sh --to pdf --defaults /data/myproject/defaults.yaml --defaults /data/defaults.yaml`


## Runtime dependecies

- a container runner - podman

  uses container image `pandoc/extra`


## Bundling a new pandoc.sh script

### Build-time dependecies

`a c compiler, make`

### Bundling

cd into scripts and run `make pandoc.sh` which will build `scripts/pandoc.sh` copy this script the root of your repo or `PATH`
