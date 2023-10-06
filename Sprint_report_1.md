# Sprint 1 Report (8/21/2023 - 10/5/2023)
# Sprint Video [Link](https://www.youtube.com/watch?v=yz-D5rAdPVk)
## What's New (User Facing)
### AI Team
An AI-Assistance report has been developed and is currently being used for analyzing ChatGPT's involvement in developing the first Homework assignment. Working on the assignment with the assistance of ChatGPT has been challenging so far.
### Non-AI Team

Production has been started on Homework assignment 1, which involves creating a parser for the C- language using Flex and Bison. We learned a lot about comiplers and C- given we have never worked with either.

## Work Summary (Developer Facing)
### AI Team
We have started developing the first homework assignment with the assistance of ChatGPT version 3.5. It has assisted in the development of a Flex and Bison scanner/parser. ChatGPT currently faces issues with understanding the assignments problems. It is attempting to solve problems, but is failing to properly address all the errors.

ChatGPT sometimes struggles with understanding C- code. With preliminary testing, we found that it does not have a good understanding of C- code. As we continue to develop, it seems that it is starting to understand what it is needing to do. However, it still has significant problems which are being addressed as we continue to develop the project.
### Non-AI Team
We have begun working on the first homework assignment. This assignment has us creating a parser for the C- language using Flex and Bison. We have run into struggles as we do not have access to any of the previous lecture videos. As Flex and Bison are not as frequently used as many other CS topics, searching for answers to our questions has also become difficult.

One of the primary obstacles we have encountered is the unavailability of previous lecture videos that could have provided valuable insights and guidance for this specific task. As Flex and Bison are not as commonly used as some other topics in computer science, finding relevant resources and solutions to our questions has proven to be difficult. Nevertheless, we remain committed to overcoming these challenges and completing the assignment successfully.


## Unfinished Work
### AI Team
We have made some progress on implementing Homework 1. Fixing the AI's code has proven challenging, but we have been making progress in doing so. Currently we are being held back by ChatGPT's ability to handle the errors. It struggles to identify the real issue causing the errors in the code it provided even with directions. 
Even with these challenges, the rate of progress has continued to improve, and we believe it will become easier as the prompts continue.
### Non-AI Team
While we have made progress on the parser, there are still some unresolved issues related to specific rules and characters within the C- language. We have identified the lines of code that are causing errors and have marked them for further investigation and resolution. However, we are currently facing difficulties in determining the appropriate strategies to address these issues effectively.

We will continue to collaborate and explore various solutions to resolve these problems and ensure the parser functions correctly.

## Completed Issues/User Stories
### AI Team
All Issues are under development pending consistent change due to AI involvement.
### Non-AI Team
1. **Create Makefile** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/3)
   - Assigned to: Adam Karaki
   - Story Points: 3
   - Description: Developed a Makefile to streamline the project's build process. This Makefile defines compilation rules and dependencies, making it easier for the team to build the project consistently.

2. **Build Bison Parser** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/2)
   - Assigned to: Adam Karaki
   - Story Points: 5
   - Description: Successfully built the Bison parser for the C- language as part of Homework Assignment 1. The parser is now capable of recognizing and processing C- language constructs, a crucial step in completing the assignment.

3. **Implement Flex Scanner** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/1)
   - Assigned to: Evan Smith
   - Story Points: 4
   - Description: Completed the implementation of the Flex scanner for the C- language. The scanner is now capable of tokenizing input source code, providing essential input to the Bison parser. This work represents a significant milestone in the assignment's progress. 

Each of these tasks has been successfully completed, contributing to the overall advancement of Homework Assignment 1 and our project's objectives.

## Incomplete Issues/User Stories
### AI Team
1. **Fix scanType.h** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/6)
   - Assigned to: Cameron Kinney
   - Story Points: 1
   - Description: The scanType enum declaration conflicts with other defined/declared variables. Prompt the AI for fixes and adapt.
2. **The Bison Part** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/7)
   - Assigned to: Ayush Kumar
   - Story Points: 3
   - Description: Modify the Bison Part once the AI completes the error fixing implementation.
3. **The Flex Part** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/8)
   - Assigned to: Cameron Kinney
   - Story Points: 3
   - Description: Ensure warnings were properly fixed with the updated token handling.
4. **Build and Test** (Milestone: Sprint 2) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/9)
    - Assigned to: Ayush Kumar & Cameron Kinney 
    - Story Points: 1
    - Description: Implement test functions and validate all test cases.
### Non-AI Team
Here are links to issues we worked on but did not complete in this sprint:

1. **Parser Error Resolution** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/5)
   - Assigned to: Adam Karaki
   - Story Points: 3
   - Description: The parser presents some errors on a few lines, but we have not found enough details on how to address the errors, just their location.

2. **Parser Character Errors** (Milestone: Sprint 1) [Link](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/4)
   - Assigned to: Evan Smith
   - Story Points: 4
   - Description: The parser works for some errors, but we have run into problems with getting errors for some characters.


## Code Files for Review
### AI Team
Please review the following code files, which were actively developed during this sprint, for quality:
* [makefile](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/AI/makefile)
* [parser.l](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/AI/parser.l)
* [parser.y](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/AI/parser.y)
* [scanType.h](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/AI/scanType.h)

### Non-AI Team
Please review the following code files, which were actively developed during this sprint, for quality:
* [parser.l](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/parser.l)
* [parser.y](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/parser.y)
* [mk.sh](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/mk.sh)
* [header.h](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/header.h)

## Retrospective Summary
### AI Team
Here's what went well:
- **Development of AI Statistics Report:** We developed a report sheet which describes each interaction with the AI in depth for all users/developers to reference when needed during reviews. It allows us to keep a consistent log of when the AI is beneficial and not beneficial.
- **Development of HW1 with AI Involvement:** Although the process has proven difficult, the interactions with the AI have improved since the beginning stages of the project. We are learning to receive more valuable and appropriate responses as we ask the AI more questions.
- **Analysis of the AI responses:** Even with the AI giving insufficient fixes or responses, we are mostly understanding where it is failing.

Here's what we'd like to improve:
- **Issue Tracking:** Our issue tracking is lacking due to the way we have been developing with the AI. We are looking at better ways of handling issue tracking in regards to the AI performing significant assignment-wide changes.
- **AI Error Handling:** Currently with the AI producing code riddled with errors, we are aiming to improve how we can break down the assignment portions across dialogues while preserving integrity of the assignments and chats.
- **Overall Efficiency:** The process of handing the AI the prompt, analyzing the response, implementing, and re-analyzing is slow. We are reevaluating our process to produce an efficient product.

Here are changes we plan to implement in the next sprint:
- **Finishing HW1-AI: The Scanner:** This is our most important task. We will tackle all current open issues and update them as we complete portions.
- **Finishing HW2-AI: The Parser:** We plan to be finished with the second AI assisted assignment by the next sprint.
- **Beginning/Completing HW3-AI: Semantic Analysis and Typing:** We plan to be partially through HW3 by the end of the next sprint. We are aiming to finish the semantic analysis and typing by the end of the sprint since we believe the development process will significantly improve as development continues.
### Non-AI Team

What Went Well:

- **Progress on C- Parser:** Despite the challenges we faced, we made significant progress on developing the C- language parser using Flex and Bison. We successfully initiated this crucial task and laid the foundation for its completion.

- **Team Collaboration:** Our team demonstrated excellent collaboration and communication skills during this sprint. Despite the unique difficulties associated with our task, we actively shared knowledge and supported each other in problem-solving.

- **Initial Assignment Progress:** We made headway in Assignment 1, which involved the creation of a Makefile and building the Bison parser. These accomplishments are essential steps toward fulfilling the assignment's requirements.

What We'd Like to Improve:

- **Access to Resources:** One of the challenges we faced was the lack of access to previous lecture videos, which could have provided valuable guidance. We aim to address this by exploring alternative resources or seeking assistance from instructors to bridge this knowledge gap.

- **Troubleshooting Difficulties:** While we have identified errors in the parser, we encountered difficulties in finding detailed solutions to address these issues. Improving our troubleshooting skills and exploring online forums or textbooks dedicated to Flex and Bison will be a focus area for improvement.

- **Efficiency in Assignment Completion:** To enhance our efficiency in completing assignments, we intend to refine our workflow and task management. This will involve better milestone tracking and setting clearer objectives for each sprint.

Changes Planned for the Next Sprint:

- **Finishing of Non-AI's C- Parser:** Our top priority for the next sprint is to resolve the issues in the C- language parser that we started in this sprint. We plan to address the errors and ensure the parser functions correctly.

- **Beginning and Finishing Assignment 2 for Non-AI:** We aim to initiate and successfully complete Assignment 2 for the non-AI team during the next sprint. This will require effective task allocation and time management.

- **Continuous Learning:** We will proactively seek resources and training materials to improve our understanding of Flex and Bison, ensuring we have the necessary knowledge and skills to overcome challenges in future tasks.
