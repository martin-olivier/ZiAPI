# Contributing to ZIAPI

## Issues

Issues are more than welcome. When submitting an issue make you sure to select the right issue template for your need.

### Bug Reports

Submit a bug report when an implemented feature isn't working properly (e.g. the CMake intergation refuses to build).

### Feature Requests

If you feel like something is missing from the ZIAPI, like a new feature or a tweak to an existing one, submit a feature request describing your feature and some justification on why it should be implemented.

## Pull Requests

Pull requests are more than welcome. Usually it's best to start by opening an issue and to follow it up with a pull request once everyone agrees on how to fix the bug / implement the feature.

## Conventions

**Git Commits**

We use the [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/) specification for git commits.

**Git Branches**

We use the following syntax for naming git branches

```
<keyword>/<branch_name>-<issue_id>

feat/billing-module-76
fix/http-header-parser-167
fix/module-loader-12
```

Some branches like `main`, `dev`, `hotfix` do not follow that convention.

**C++**

We use the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html).

**Issues and Pull Requests**

Make sure your pull request and issue names are human readable titles such as `Missing const qualifier on method` for an issue or `Support for HTTP 3` for a pull request.
