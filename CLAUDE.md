# PullWeight (C++)

PullWeight is a Group Project Contribution Tracker. The name comes from "pull your weight" (doing your fair share).

## What this project is
A console-based C++ program that tracks who did what in a college group project and produces a fair contribution report. It is a **pure OOP showcase project** for placement interviews, so clean class design matters more than features.

Core flow:
1. A project is created with a deadline, team members and a Guide (teacher).
2. Tasks of different types are added and assigned to members.
3. Members move tasks through: NOT_STARTED -> IN_PROGRESS -> SUBMITTED -> APPROVED (or REJECTED).
4. A task needs proof (commit link / file name) and approval from someone other than the person who did it.
5. Approved tasks give points. Each task type calculates points differently. Late tasks lose 20%.
6. At the end, members rate each other (1-5). Ratings pass through anti-bias checks.
7. Final score = 70% task points + 30% peer rating (weighted by rater credibility).
8. A contribution report shows each member's percentage, with warnings.

## Owner and style rules
- The owner is a student learning OOP for interviews. After every change, explain in **simple, plain English** what you did and which OOP concept it shows.
- Do ONLY the phase asked for. Do not jump ahead or add extra features.
- Keep code readable over clever. Add short comments on any line that shows an OOP concept (for example `// Runtime polymorphism`).
- After finishing a phase, compile and run it, and fix all warnings.

## Git and GitHub (do this at the end of EVERY phase)
- GitHub repository: https://github.com/jiya-agarwal29/PullWeight (branch `main`).
- In Phase 0 only: run `git init`, `git branch -M main`, and `git remote add origin https://github.com/jiya-agarwal29/PullWeight.git` if the remote is not already set.
- At the end of every phase, ONLY after the build succeeds with no warnings and the program runs:
  1. `git add .`
  2. `git commit -m "Phase N: <short description>"` (for example `Phase 1: people classes and diamond inheritance`)
  3. `git push -u origin main` (plain `git push` after the first time)
- Never commit build output (the `.gitignore` handles it). Never force-push.
- If the push fails (login, network, conflict), stop and explain the error in simple English instead of trying risky fixes.
- Mention the commit message and push result in the phase summary.

## End-of-phase summary (do this at the end of EVERY phase)
Do NOT write documentation files. The owner keeps the documentation separately.
Instead, at the end of each phase, print a DETAILED summary in this exact format so she can copy it. Be complete; it is used to write in-depth documentation.

```
PHASE N SUMMARY
1. Files created/changed: every file, one line each on what it holds.
2. Classes: for each class -> purpose; every data member with its type and access level (private/protected/public); every method with its signature and one line on what it does.
3. Relationships: who inherits from whom (and how: virtual, public), who owns or holds whom, and which smart pointer is used.
4. Key code: the 3-5 most important snippets (5-20 lines each), each with a note on what it shows.
5. OOP / C++ concepts: each concept used, the exact class and method where it appears, and why it was needed there.
6. Design decisions: each choice made, alternatives considered, and why they were rejected.
7. Errors hit: the exact error messages, what caused them, and how they were fixed (write "none" if none).
8. How to run: the commands, and the full program output.
9. Git: the commit message, and whether the push succeeded.
```

## Technical rules
- Language: **C++17**. Compiler: g++ with `-std=c++17 -Wall -Wextra`.
- No external libraries. Only the standard library (STL).
- Everything lives in `namespace pullweight`.
- Declarations in `include/*.h`, definitions in `src/*.cpp`. Templates stay fully in headers.
- Use `#pragma once` in every header.
- Use smart pointers, never raw `new`/`delete` in project code:
  - `std::unique_ptr<Task>` inside `Project` (composition: project owns tasks)
  - `std::shared_ptr<Member>` for members (aggregation: members live independently)
- Use `const` correctly (const methods, const references).
- Build with `make`. Run with `./pullweight`.

## Folder structure
```
PullWeight/
├── include/
│   ├── Person.h  Member.h  Guide.h  TeamLead.h
│   ├── Task.h  CodingTask.h  BugFixTask.h  DocTask.h  DesignTask.h  TestingTask.h
│   ├── TaskStatus.h  TaskFactory.h
│   ├── PeerReview.h  Project.h  ContributionReport.h
│   ├── Repository.h  ProjectManager.h  Notifiable.h  Exceptions.h
│   └── validators/
│       ├── RatingValidator.h  OutlierRemover.h  BiasedPairDetector.h
│       └── EvidenceMismatchChecker.h  ReasonRequiredCheck.h
├── src/            (one .cpp per class, same names, validators/ subfolder)
├── main.cpp
├── Makefile
└── README.md
```

## Class design (follow this)
- `Person` (abstract): id, name. Pure virtual `display()`. Virtual destructor. Static `nextId`.
- `Member` : **virtual public** Person. private score, credibility. Can do tasks, give ratings.
- `Guide` : **virtual public** Person. The teacher/project guide. Approves tasks, resolves flagged ratings. Does not do tasks or get scored.
- `TeamLead` : public Member, public Guide. Diamond problem solved with virtual inheritance. Can approve teammates' tasks but **never their own**.
- `Task` (abstract): title, difficulty, deadline, status, proof, assignee. Pure virtual `calculatePoints() const`. Virtual destructor. Copy constructor + assignment operator (Rule of Three).
- `CodingTask`, `DocTask`, `DesignTask`, `TestingTask` : Task (hierarchical inheritance), each with its own points formula:
  - CodingTask: difficulty x 10 + linesOfCode / 50
  - DocTask: pages x 3
  - DesignTask: screensOrSlides x 4
  - TestingTask: bugsFound x 5
- `BugFixTask` : CodingTask (multilevel inheritance).
- `TaskStatus`: enum class.
- `TaskFactory`: creates the right task type (Factory pattern).
- `Project`: owns tasks (`vector<unique_ptr<Task>>`), shares members (`vector<shared_ptr<Member>>`), has one Guide. Overloaded `addTask(...)` methods.
- `PeerReview`: immutable (all fields const, set in constructor only). rater, ratee, rating, reason.
- `RatingValidator` (pure abstract = interface) + 4 validators chained together (Chain of Responsibility):
  - OutlierRemover: drop highest and lowest rating per member
  - BiasedPairDetector: two people rate each other high while others rate them low
  - EvidenceMismatchChecker: rating far above actual task points lowers the rater's credibility
  - ReasonRequiredCheck: ratings of 1 or 5 need a written reason
- `ContributionReport`: builds the final report, with an inner class `Row`.
- `Repository<T>`: template class to store and find any type by id.
- `ProjectManager`: Singleton running the program.
- `Notifiable`: interface; members/guides get notified on assignment, submission, approval (Observer pattern).
- `Exceptions.h`: InvalidRatingException, SelfRatingException, SelfApprovalException, TaskNotApprovedException, ProofMissingException (all derive from std::exception).

## Operator overloading to include
- `operator<` on Member (compare by final score, used for sorting)
- `operator<<` as a **friend** function for Member and Task
- `operator+=` on Task (add bonus points)
- `operator==` on Person (compare by id)