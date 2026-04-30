# AGENT.md

## Repository Purpose

This workspace is used for learning and practicing algorithms.

The root `README.md` is the canonical learning roadmap for topic order, planned filenames, study pacing, and practice expectations.

## Directory Contract

- `docs/` stores algorithm notes, explanations, derivations, and related study material.
- `src/` stores the corresponding C++ implementations.

The directories may start empty. That is expected. New content should preserve the `docs/` to `src/` pairing where practical.

## Working Conventions

- Keep documentation and code aligned by topic.
- Prefer clear, minimal examples over large template-heavy code.
- Use C++ for implementation files under `src/`.
- In C++ files, document every function with a short doc comment covering:
  - function role
  - input
  - output
- In multi-step C++ functions, add short internal comments so each major part of the function is easy to scan.
- Follow the standard topic workflow defined in `README.md`:
  - `Knowledge`
  - `Implementation`
  - `Practice`
  - `Completion`
- When adding or completing an algorithm topic, add all of the following:
  - a note in `docs/`
  - a matching C++ implementation in `src/`
  - representative algorithm practice, typically LeetCode-style problems
  - completion criteria or notes on mistakes, edge cases, and debugging
- In study notes, keep the `Mistake Log` as one compact section or bullet list rather than splitting it into separate `mistake/cause/fix` fields.

## Naming Guidance

- Use descriptive topic-based filenames.
- Keep related note/code filenames close in meaning so they are easy to match.
- Prefer filenames that match the roadmap entries in `README.md`.

Examples:

- `docs/binary_search.md`
- `src/binary_search.cpp`

## Definition Of Done

A topic should be treated as finished only when:

- the note in `docs/` explains the idea clearly
- the C++ file in `src/` contains the core template and basic examples
- the related practice problems have been attempted or solved
- common mistakes, edge cases, or debugging notes are captured for later review

## Scope

This repository is for algorithm study and practice, not for production application code.
