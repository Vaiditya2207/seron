This directory contains the following typescript projects. 
More information can be obtained on each project by navigating to their respective directories.

- `extension-manager`: a node process meant to be spawned by the main seron executable, ready to load and unload extension workers on-demand.
- `@seron/api`: the seron SDK used to build extensions, as published on npm
- `@seron/raycast-api-compat`: a private package that provides a raycast-compatible way to use the `@seron/api` package. It is a mere wrapper around it.

# Integration with the build system

All the projects in this directory are bundled inside a single javascript file which is then executed at startup.

The `@seron/api` package is also published on npm on every release, and follows the main versioning scheme.
