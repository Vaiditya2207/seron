This package lets you extend the [Seron](https://docs.seron.com/) launcher using React and TypeScript.

[![Version](https://img.shields.io/npm/v/@seron/api.svg)](https://npmjs.org/package/@seron/api)
[![Downloads/week](https://img.shields.io/npm/dw/@seron/api.svg)](https://npmjs.org/package/@seron/api)

# Getting started

The recommend way to start developing a new extension is to [read the docs](https://docs.seron.com/extensions/introduction).

The full API reference (expect breaking changes) can be found [here](https://api-reference.seron.com).

# Installation 

Install the package:

```
npm install @seron/api
```

# Versioning

The `@seron/api` package follows the same versioning as the main `seron` binary, since the API is always embedded in the binary.

# CLI usage

The package exports the `vici` binary which is used to build and run extensions in development mode.

While convenience scripts are already provided in the boilerplate, you can still call the binary manually:

```bash
npx vici --help

# assuming seron is running
npx vici develop

npx vici build -o my/output/path
```
