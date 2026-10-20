# PullWeight (C++)

PullWeight is a Group Project Contribution Tracker. The name comes from "pull your weight" (doing your fair share).

## What this project is
A console-based C++ program that tracks who did what in a college group project and produces a fair contribution report. It is a **pure OOP showcase project** for placement interviews, so clean class design matters more than features.

Core flow:
1. A project is created with a deadline, team members, exactly one TeamLead and a Guide (teacher). PullWeight can hold MULTIPLE projects on one laptop; each project is saved in its own file (`data/<project-name>.txt`). The TeamLead runs their project, so OPENING a project requires that project's TeamLead PIN. A laptop only holds the projects its owner leads.
2. Tasks of different types are added and assigned to members.
3. Members move tasks through: NOT_STARTED -> IN_PROGRESS -> SUBMITTED -> APPROVED (or REJECTED).
4. A task needs proof (commit link / file name) and approval. ONLY the TeamLead or the Guide can approve. Nobody approves their own task, so the TeamLead's own tasks must be approved by the Guide, and that approval needs the Guide's PIN (the TeamLead usually runs the program, so this stops them approving as the Guide).
5. Approved tasks give points. Each task type calculates points differently. Late tasks lose 20%.
6. At the end, a rating session is held on the laptop running PullWeight: each member enters their own PIN and rates EVERY other member (1-5) in private, never themselves (the program skips their own name). Each member can submit ratings only once. A rating of 1 or 5 needs a short reason. The TeamLead rates and is rated like any member; the Guide does not rate and is not rated. The screen clears before the next member. Nobody sees who rated whom; only final scores are shown. Ratings pass through anti-bias checks.
7. Final score = 70% task points + 30% peer rating (weighted by rater credibility).
8. A contribution report shows each member's percentage, with warnings.
9. Every action (task added, assigned, started, submitted, approved, rejected, member added, rating session completed) is recorded in an append-only activity log with date, time, who did it, and details (proof link, rejection reason, points). Entries are never edited or deleted. History can be viewed by task, by member, or for the whole project.
10. All data, including the activity log, is saved to the project's own file automatically after every change. On startup PullWeight lists the saved projects; the user picks one (TeamLead PIN required) or creates a new one, and can switch projects from the menu. So the TeamLead can run PullWeight for the whole project, over weeks or months, without re-entering anything. Members send proof links to that person, who enters them.

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
Instead, at the end of each phase, ALWAYS print the full 9-part summary below, even if the phase prompt asks for a shorter explanation (give the short explanation too, then the summary). Print a DETAILED summary in this exact format so she can copy it. Be complete; it is used to write in-depth documentation.

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
- Never commit the `data/` folder (project files, `.tmp`, `.bak`); team data is private.
- The owner is on Windows. Build with `mingw32-make` (plain `make` is not installed). Run with `.\pullweight.exe` (or `./pullweight` in Git Bash).
- The "NativeCommandError" text PowerShell shows during `git push` is only git's progress output; check for `main -> main` to confirm the push worked.

## Folder structure
```
PullWeight/
├── include/
│   ├── Person.h  Member.h  Guide.h  TeamLead.h
│   ├── Task.h  CodingTask.h  BugFixTask.h  DocTask.h  DesignTask.h  TestingTask.h
│   ├── TaskStatus.h  TaskFactory.h  Date.h
│   ├── Serializable.h  Storage.h  FileStorage.h
│   ├── PeerReview.h  Project.h  ContributionReport.h  LogEntry.h  ActivityLog.h
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
- `Person` (abstract): id, name, PIN (4 digits, private, stored as a hash, never printed). `checkPin(const std::string&) const`. Pure virtual `display()`. Virtual destructor. Static `nextId`.
- `Member` : **virtual public** Person. private score, credibility. Can do tasks, give ratings.
- `Guide` : **virtual public** Person. The teacher/project guide. Approves tasks (always needed for the TeamLead's own tasks, with the Guide's PIN), resolves flagged ratings. Does not do tasks or get scored.
- `TeamLead` : public Member, public Guide. Diamond problem solved with virtual inheritance. Approves teammates' tasks (no PIN needed) but **never their own**.
- `Task` (abstract): title, difficulty, deadline, status, proof, assignee. Pure virtual `calculatePoints() const`. Virtual destructor. Copy constructor + assignment operator (Rule of Three).
- `CodingTask`, `DocTask`, `DesignTask`, `TestingTask` : Task (hierarchical inheritance), each with its own points formula:
  - CodingTask: difficulty x 10 + linesOfCode / 50
  - DocTask: pages x 3
  - DesignTask: screensOrSlides x 4
  - TestingTask: bugsFound x 5
- `BugFixTask` : CodingTask (multilevel inheritance).
- `TaskStatus`: enum class.
- `Date`: value class for real calendar dates (YYYY-MM-DD), with `today()`, `fromString()`, `toString()`, and operators `<`, `==`, `-` (days between), `<<`. Used for deadlines, submittedOn and approvedOn.
- `TaskFactory`: creates the right task type (Factory pattern).
- `Project`: owns tasks (`vector<unique_ptr<Task>>`), shares members (`vector<shared_ptr<Member>>`), has one Guide and exactly one TeamLead (`getTeamLead()`; adding a second TeamLead is refused). Overloaded `addTask(...)` methods.
- `PeerReview`: immutable (all fields const, set in constructor only). rater, ratee, rating, reason.
- `LogEntry`: immutable record of one action: date, time (HH:MM from the system clock), actorId, action (enum class `Action`), taskId (or -1), details. Implements Serializable.
- `ActivityLog`: append-only list of LogEntry owned by Project (composition). Only `record(...)` adds entries; there is no edit or delete method. Filters: `forTask(id)`, `forMember(id)`, `all()`, `lastActivityOf(memberId)`.
- `RatingValidator` (pure abstract = interface) + 4 validators chained together (Chain of Responsibility):
  - OutlierRemover: ONLY when the team has more than 5 members (6+), drop each member's highest and lowest rating; for 5 or fewer members it keeps all ratings and passes them on unchanged (too few ratings to drop any)
  - BiasedPairDetector: two people rate each other high while others rate them low
  - EvidenceMismatchChecker: rating far above actual task points lowers the rater's credibility
  - ReasonRequiredCheck: ratings of 1 or 5 need a written reason
- `ContributionReport`: builds the final report, with an inner class `Row`.
- `Repository<T>`: template class to store and find any type by id.
- `ProjectManager`: Singleton running the program. Lists the saved projects in `data/`, creates new ones, opens one (only after `checkPin` on that project's TeamLead), holds the currently open project, and switches between projects (saving the current one first).
- `Notifiable`: interface; members/guides get notified on assignment, submission, approval (Observer pattern).
- `Serializable`: interface with `serialize() const`; every saved class implements it, and has a matching `fromRecord(...)` to rebuild itself.
- `Storage`: interface with `save(const Project&)` and `load()`. `FileStorage` implements it with one plain-text file per project, `data/<project-name>.txt` (the file name is passed in from outside; project names are turned into safe file names), safe writing (.tmp then replace, keep .bak), and restores id counters after loading. Nothing else depends on `FileStorage` directly (Dependency Inversion).
- `Exceptions.h`: InvalidRatingException, SelfRatingException, SelfApprovalException, NotAuthorizedException (a plain member tries to approve), WrongPinException, AlreadyRatedException (a member rates the same person twice), TaskNotApprovedException, ProofMissingException, DataFileException (all derive from std::exception).

## Operator overloading to include
- `operator<` on Member (compare by final score, used for sorting)
- `operator<<` as a **friend** function for Member and Task
- `operator+=` on Task (add bonus points)
- `operator==` on Person (compare by id)
