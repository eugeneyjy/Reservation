# Reservation

## Assignment Description
A Teppanyaki Japanese restaurant serves supreme quality meal for their guests. Guests have a
front row seat on how Master chef prepares their dishes. Their authentic setting places guests
in a traditional Japanese style establishment and fits perfectly to its cuisine and feel.

Due to popular demand and limited seating availability, guests have to reserve seats at least 3
days in advance for enjoying meal at their restaurant. The restaurant only serves 4 sessions
(11:00am – 12:30pm, 12:30pm – 2:00pm, 5:00pm – 6:30pm and 6:30pm – 8:00pm) each day
and each session only serves 8 guests.

Write an application in C++ to process reservation records. The reservation records should be
read from a text file when the program is loaded for execution. Gather data on at least 20
reservation records and prepare them in the text file. As each record is read, insert it into a list
by using nested array of structures.

After building the list, display a menu with the following options:
(a) **List** – Display the reservation records. Each display should contain an appropriate
heading and column captions.
(b) **Search for availability** – Search for the availability in the list using the date, time and
number of guests.
(c) **Update reservation record** – Ask user for date, time and number of guests. Then
search for availability in the list using the input data; reservation record should be
updated if available.
(d) **Exit** – Stop the program. The program will write the updated data in the list to the
file.

## Advanced Questions
**Task1: Maintaining contact information of guests**

Modify the storage structures of reservation records and implementations in your program, so
that it can store not only number of guests in each session but also contact information of
guests.

**Task2: Add an additional item to your menu: Advanced Search**

Search for guest record(s) in the list using the name or phone number, and print the full
details for the record(s). It can match word(s)/number within a string/number, and also print
multiple results. This is best explained by the following examples:
- If the full name “**Paul J. Deitel**” is stored inside the list, searching for either “**Paul**” or
“**Deitel**” should return the record.
- If the phone numbers “**012-3214567**”, “**012-3314567**”, and “**012-3414567**” are in the list,
then searching for “**14567**” must print all three records (because the number “14567”
occurs in all three phone numbers).
Note that you may need to use `strstr()` which allows you to locate substring.

Prepare the necessary data file(s) for building the data structure(s) needed in your application.
You may give additional assumptions for your application.

#### Additional Information
To make your program more robust and avoid problems at run time, do as much status/error
checking as you could in your program. You may also add on more features in your program
for enhancement.

## Assessment and Submission
This is a group assignment. Form a group of 2 or 3 members, preferably from same
programme as yours. Prepare a report (preferable using word processing software and export
to portable document format) to answer the questions given above.
Your **REPORT SHOULD CONTAIN** the following:
  1. design of the application (structure chart and flowcharts/pseudocode)
  2. print out of the C++ program.
  3. sample output(s) (Alt+Prnt Scrn) of your program.
  4. sample of input data and test cases
Do remember to print the assignment marking sheet and attach as the FIRST PAGE of your
report. There will be a link created in WBLE subject page for you to submit softcopy of your
**report**, **C++ program file(s)** and **input text file(s)**. You are required to upload the soft copy
of your works by the deadline. Late submission will not be entertained.
This practical assignment will contribute 20% of your final mark. Refer to the marking sheet
for the mark allocations for the report and C++ program. The report will be marked for
correctness, completeness, presentation style, and relevant use of diagrams/tables/graphs,
etc. And the C++ program will be marked for correctness, completeness, program style,
adequate testing and documentation/comments. It’s your responsibility to understand the
requirements of the tasks and prepare well for your submission. You will not receive full
mark if you do not submit the report and C++ program that is a reasonable attempt and
compiles without error. You might be asked questions about the works you submit to ensure
that you understand them.

## Plagiarism
It is important that your solutions to the practical assignment be your own work. It is
perfectly acceptable to seek help and advice when completing the practical assignment, but
this must not be taken to the point where what is submitted is in part someone else's work.
