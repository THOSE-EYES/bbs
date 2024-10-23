# Contributing to the Better Build System (BBS)

The following is a summary of the process for contributing changes to the Better Build System (BBS). For detailed information, please refer to the [Better Build System (BBS) Development Guide](https://google.github.io/styleguide/cppguide.html).

## Patches

The Better Build System (BBS) uses GitHub for development and code review. To contribute patches:

1. Fork the upstream [Better Build System (BBS) Repository](https://github.com/THOSE-EYES/bbs) into your personal GitLab account.
2. Refer to the [Building Guide](README.md#building-the-better-build-system) for instructions on building the project locally.
3. Follow the [Source Code Guidelines](https://google.github.io/styleguide/cppguide.html) for coding standards.
4. Create a topic branch with a descriptive name for your work. Start from the `main` branch for new work. Use the `release` branch only for fixes targeting specific releases.
   - If uncertain, default to `main`. Reviewers might request a rebase if needed.
5. Make commits with clear, incremental, and logically complete changes, using the [.gitmessage](.gitmessage) file.
6. Push your topic branch to your personal repository fork on GitLab.
7. Create a Merge Request targeting the `main` branch (even for changes intended for `release`). Enable the option to "Allow commits from members who can merge to the target branch" so maintainers can make minor edits if necessary.

## License

We do not require any formal copyright assignment or contributor license agreement. Contributions submitted to the Better Build System (BBS) are assumed to be offered under the Apache License. See [LICENSE.md](LICENSE.md) for details.
