# Sprint 4 Report (2/3/2024 - 3/2/2024)
## Sprint Video [Link](https://youtu.be/iRcMLkzRI_c)

## What's New (User Facing)
### AI Team
 * The AI team has completed the development of the JSON parser in Python for our database application, marking a significant milestone in our project.

### Non-AI Team
 * The Non-AI team has finished development of the User-Interface (UI), using the Qt framework, for our Yelp application. It allows any user to interact with the application, regardless of development knowledge.

## Work Summary (Developer Facing)
### AI Team
The AI team has achieved a milestone by successfully concluding the JSON Parser for our database application using python.This development enables us to parse businesses based on a specified state, city, or ZIP code, providing valuable insights into successful businesses in these regions. Furthermore, the parser categorizes these businesses, offering a comprehensive overview of their respective industries. This accomplishment enhances the capabilities of our application, contributing to a more insightful analysis of business data.

### Non-AI Team
The Non-AI team finished the development of the UI using the Qt framework. Each part of the UI is complete, awaiting the insertion of the parsed data for the states and zipcodes. We have created a simple user-friendly interface for anyone to use. Each portion of the UI is contained in a Qt groupbox for cleanliness. Each element is labeled with a unique name to prevent potential developer errors during development. The UI is one of the most important aspects of the Yelp application moving forward.  

## Unfinished Work
### AI Team
We were unaware that we had to display the noSQL or JSON data to the frontend, so we still have to complete that for our second milestone.

### Non-AI Team
Currently, we are continuing development with parsing all data files into the UI. We are able to parse the input data into the console. Our current development is focusing on parsing the states and zipcodes into the UI.  

## Completed Issues/User Stories
### AI Team
Here are links to the issues that we completed in this sprint:
 * [69](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/69)
 
### Non-AI Team
Here are links to the issues that we completed in this sprint:
* [67](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/67)
* [68](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/68)

 ## Incomplete Issues/User Stories
 ### AI Team
 Here are links to issues we worked on but did not complete in this sprint:
 * [72](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/72)
 * [73](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/73)
 
 ### Non-AI Team
* [73](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/issues/73)

## Code Files for Review
### AI Team
Please review the following code files, which were actively developed during this sprint, for quality:
 * [JSON Parser](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/blob/AI/JSONParser.py)

### Non-AI Team
Please review the following code files, which were actively developed during this sprint, for quality:
* [UI](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/tree/Non-AI)
* [Yelp](https://github.com/WSUCptSCapstone-F23-S24/inst-aiassistedassignmentcompletion/tree/Non-AI)

## Retrospective Summary
### AI Team
Here's what went well:
  * Completion of JSON parser
    
Here's what we'd like to improve:
   * Our understanding of how to organize data to display items to frontend
  
Here are changes we plan to implement in the next sprint:
   * We plan to start working on showing the data to the frontend
   * We plan to start working on the Database server

   
### Non-AI Team
Here's what went well:
  * Completion of the UI
  * Parsing data files
 
Here's what we'd like to improve:
   * Understanding the query process for the UI data 
  
Here are changes we plan to implement in the next sprint:
   * We plan on completing the data insertion to the UI
   * We also plan on completing the queries to the UI when state and zipcodes are selected
