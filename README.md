# REDME.md

This is a possible implementation of a server for an online library application. The server uses a communication protocol to receive commands from a client application, parses the received command, accesses the database to perform operations, and returns the result to the client. In this implementation, SQL Server specific queries and functions were used.

### Protocol used:
[id_prot]/[parameters]

### CLIENT -> SERVER
- Exit 					(for the logout/force close button)
- 1/username/password 	(for the login button)
- 2/SubscriptionType/ClientType/username/password/password2/name/surname/occupation/CNP/Email/Phone (for the register button)
- 3/ 					(for the profile button)
- 4/ 					(for displaying borrowed books)
- 5/BookName 			(for extending the deadline)
- 6/newPassword 		(for modifying account -> password)
- 7/newEmail 			(for modifying account -> email)
- 8/newPhone 			(for modifying account -> phone)
- 9/search sequence 	(for the search bar on the client/librarian page)
- 10/BookName 			(for displaying book details)
- 11/BookName 			(for the reserve button)
- 12/BookName 			(for the return button)
- 13/BookName			(for the download book button)

### Adding an Article:
- Book: 14/ArticleType/SubscriptionID/Name/Author/PublicationDate/Publisher/NumberOfPages/Copies/Description/Image/PDF
- Magazine: 14/ArticleType/SubscriptionID/Name/PrintDate/Publisher/NumberOfPages/PDF
- Newspaper: 14/ArticleType/SubscriptionID/Name/PrintDate/PDF

- 15/ 					(for the "Imprumuturi" button in table 20 -> will display all loans made by clients)
- 16/BookName/WhatToModify/newValue/... (for the modify book button -> will give the column to be modified and the new value)
- 17/BookName 			(for the delete book button)
- 18/ 					(for the schedule button)
- 19/ 					(for the contact button)

### SERVER -> CLIENT
- "Deconectare cu succes"
- 1/Error* || 1/Client || 1/Librarian
- 2/Error* || 2/Succeded
- 3/Error* || 3/SubscriptionType/Username/Name/Surname/Occupation/CNP/Email/Phone
- 4/Error* || 4/1/username/BookName1/LoanDate1/ReturnDate1/2/username/BookName2/LoanDate2/ReturnDate2/...
- 5/Error* || 5/Succeded
- 6/Error* || 6/Succeded
- 7/Error* || 7/Succeded
- 8/Error* || 8/Succeded
- 9/Error* || 9/title1/title2/.../titley -> titles found that BEGIN with the sequence written by the client

- Book: 		10/Error* || 10/SubscriptionType/Name/Author/PublicationDate/Publisher/NumberOfPages/Copies/Description/Image/PDF
- Magazine: 	10/Error* || 10/SubscriptionType/Name/PrintDate/Publisher/NumberOfPages/PDF
- Newspaper: 	10/Error* || 10/SubscriptionType/Name/PrintDate/PDF

- 11/Error* || 11/Succeded
- 12/Error* || 12/Succeded
- 13/Error* || 13/Succeded
- 14/Error* || 14/Succeded
- 15/Error* || 15/1/username/BookName1/LoanDate1/ReturnDate1/2/username/BookName2/LoanDate2/ReturnDate2/...
- 16/Error* || 16/Succeded
- 17/Error* || 17/Succeded
- 18/Error* || 18/schedule
- 19/Error* || 19/contact information

### Types of Errors
- "No command" 						(Command does not start with a number)
- "Invalid command" 				(Command given does not start with a valid number and is not Exit)
- "x/Invalid command" 				(Command given for option x is incorrect)
- "x/ActionDenied" 					(User attempted to execute a command they are not allowed to)
- "QueryCreationError" 				(Error in creating a query)
- "QueryExecutionError" 			(Error in executing a query)
- "1/Wrong username or password" 	(User not found in database)
- "2/Incorrect password" 			(Confirmation password does not match register password)
- "2/Username unique"				(User's username must be unique in the database)
- "2/Wrong username" 				(User's username must not contain the '/' character)
- "11/Not enough books" 			(No more physical copies available for a certain book)

### Restrictions
- Librarians cannot:
    - borrow books
    - return books
    - extend the due date of borrowed books
    - display borrowed books

- Clients cannot:
    - add articles
    - modify articles
    - delete articles
    - display all borrowed books (including those borrowed by other users)

- Only books can be borrowed in physical format
- In online format, books, magazines, or newspapers can be downloaded
- All dates will be sent/received in the format yyyy-mm-dd
- Online books are PDFs uploaded to Google Drive
- The client receives a code that represents the PDF code and incorporates the code into one of the following URL addresses:
    - https://docs.google.com/uc?export=download&id=*CODE* (to download the PDF)
    - https://drive.google.com/file/d/*CODE*/view?usp=sharing (to open the PDF in a web page)