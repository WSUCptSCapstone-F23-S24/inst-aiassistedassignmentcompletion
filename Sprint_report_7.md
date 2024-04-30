# Sprint 7 Report (3/2/2024 - 4/2/2024)
## Sprint Video [Link](https://youtu.be/qIdEcB530WM)

## What's New (User Facing)
### AI Team
 * The AI team has completed the development of the database (milestone 3) in Python for our database application, marking a significant milestone in our project.

### Non-AI Team
 * The Non-AI team completed milestone 2 during this sprint. The Qt Framework UI has States, Cities, and Zip Codes for the user to interact with.
 * The Non-AI team also finished development of a file parser using Python and a database using pgAdmin for our third milestone.

## Work Summary (Developer Facing)
### AI Team
The AI team has achieved a milestone by successfully concluding the SQL for our database application using Python. The final task we needed to finish as part of our project was displaying the data for each zip code. We obtained the data from the Yelp website, and modified our code to parse the downloaded JSON. From there, we added queries to get the information connected to the selected zip code and display them to the marked labels.

### Non-AI Team
The team made significant significant progress during this sprint. Since we were unable to finish the second milestone before the previous sprint, the team was able to finish a full implementation of a Qt Framework UI with various data for user use. The UI populates is populated with states, cities, and zip codes. All of the data has been was successfully parsed with all duplicate elements removed to prevent the UI from showing multiple states, cities, or zip codes. Along with the second milestone, the team has a completed a Python parser which traverses all of the data in the four files. It performs SQL insertion as it reads the data using the psycog2 library to connect to the pgAdmin 4 database. All SQL queries for data insertion, data handling, and database querying are completed. Each query is optimized to the best of our ability to reduce the time taken to insert and retreive data.


## Unfinished Work
### AI Team
We were unaware that we had a zipcode stats json file, so we still have to complete that for our third milestone.

### Non-AI Team
The Non-AI Team has not finished the UI at this time. However, our team is nearly finished, and closing in on testing the projects ability to satisfy and exceed the project requirements.

## Completed Issues/User Stories
### AI Team
Here are links to the issues that we completed in this sprint:
 * [78]((https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/78))
 
### Non-AI Team
Here are links to the issues that we completed in this sprint:
* [66](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/66)
* [68](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/68)
* [75](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/75)
* [76](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/76)
* [81](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/81)

 ## Incomplete Issues/User Stories
 ### AI Team
 All issues for the AI team have been resolved.
 
 ### Non-AI Team
* [79](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/79)
* [80](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/80)

## Code Files for Review
### AI Team
Please review the following code files, which were actively developed during this sprint, for quality:
* [Python SQL Middleware](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/AI/middleware-milestone3.py)

### Non-AI Team
Please review the following code files, which were actively developed during this sprint, for quality:
* [UI Parsing Script]([https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/tree/Non-AI](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/script.py))
* [Yelp UI Linker]([https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/tree/Non-AI](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/YelpApp.py))
* [Database Create Tables](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/create_tables.sql)
* [File/Database Parser](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/Non-AI/parseAndInsert.py)

## Retrospective Summary
### AI Team
Here's what went well:
  * Completion of Database application using SQL
  * Displaying the data of the zip codes
   
### Non-AI Team
Here's what went well:
  * Completion of the UI
  * Parsing data files
  * Database handling
  * SQL insert queries
  * SQL querying the data in the database
  * SQL query optimization
 
Here's what we'd like to improve:
   * Our knowledge of the Qt Framework, and how to improve the UI
   * Further SQL query optimization
  
Here are changes we plan to implement in the next sprint:
   * We plan on completing the UI as well as optimizing the SQL statements further 
