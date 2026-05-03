This package is intended to provide a Raycast compatible entrypoint to the seron API (`@seron/api`).
It is only meant to be bundled as part of the full javascript bundle and is not published on npm, unlike the seron API.

This is used to provide raycast extension compatibility. When a Raycast extension imports something from `@raycast/api`, we route it
to this package instead at runtime.

As of now we mostly re-export stuff that belongs to the `@seron/api` package as many signatures are the exact same.

As we continue developping the seron SDK, we don't want to limit ourselves to what Raycast offers so using this package as a bridge
solves that problem. No matter what the `@seron/api` exports, we can expose a Raycast-compatible form.
