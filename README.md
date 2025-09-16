# markdown-inheritance

A pandoc buildsystem that uses default.yaml inheritance to form metadata hierachies

TODO: make it so that the script can do inplace initialisation.

TODO: figure out if pandoc can do relative file paths from defaults.yaml files,
this makes it so absolute paths are not needed.
e.g. /data/subproject/chapter1/part1.md when in folder /data/subproject/chapter1/

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


## Types of project files

- `$repo_root/defaults.yaml` - Required

   This yaml file contains only the most basic information about the project, as well as including all filters, setting up the resource_dir, media_dir and bibilography.

   If there is only one author for all subprojects or one main author for all subprojects author information can be set in this file.

- `$subproject/defaults.yaml` - Required

   This file denotes that this folder is a subproject, and will include `details.yaml` file.

   This file also includes all the markdown files that should be built for this subproject.

   ```yaml
   input-files:
    - /data/subproject/Chapter1.md
    - /data/subproject/Chapter2.md
   ```

   This can be used to set any project specific pandoc options, such as whether to create a list of figures.

- `$subproject/details.yaml` - Required

   This file contains author metadata, and project information like document title, subtitle, date

   The reason for seperation is when a standalone file needs to built `$subproject/defaults.yaml` cannot be used as it will include all the project files.

   An example of this could be: `$subproject/additional-informational.md` this file needs to be built standalone, therefore only use `details.yaml`

- `files.yaml` - Optional, Experimental

  This file is used when a subproject markdown files need to be organised into subfolders, this could be easily added to `$subproject/defaults.yaml` but eventually it will reach a point where it will become difficult to maintain.

  This file is added to a directory and will contain the list of markdown files for that directory.

  `$subproject/chapter1/files.yaml`

  ```yaml
  input-files:
   - /data/subproject/chapter1/part1.md
   - /data/subproject/chapter1/part2.md
  ```

  `$subproject/chapter2/files.yaml`

  ```yaml
  input-files:
   - /data/subproject/chapter2/part1.md
   - /data/subproject/chapter2/part2.md
  ```

  There are two ways to use these files:

  1. append them to start of the `pandoc.sh` script as default files

     `pandoc.sh -d $subproject/chapter1/files.yaml -d $subproject/chapter12/files.yaml -d $subproject/defaults.yaml`

  2. create a `files.yaml` at the top level of the subproject that includes `files.yaml` from subfolders.

     `$subproject/files.yaml`

     ```yaml
     defaults:
      - /data/subproject/Introduction.md
      - /data/subproject/chapter1/files.yaml
      - /data/subproject/chapter2/files.yaml
     ```

     `pandoc.sh -d $subproject/files.yaml -d $subproject/defaults.yaml`


## Runtime dependecies

- a container runner - podman

  uses container image `pandoc/extra`


## Bundling a new pandoc.sh script

### Build-time dependecies

`a c compiler, make`

### Bundling

cd into scripts and run `make pandoc.sh` which will build `scripts/pandoc.sh` copy this script the root of your repo or `PATH`
