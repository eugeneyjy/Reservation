# Reservation

Assignment Description
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
(a) List – Display the reservation records. Each display should contain an appropriate
heading and column captions.
(b) Search for availability – Search for the availability in the list using the date, time and
number of guests.
(c) Update reservation record – Ask user for date, time and number of guests. Then
search for availability in the list using the input data; reservation record should be
updated if available.
(d) Exit – Stop the program. The program will write the updated data in the list to the
file.
Advanced Questions:
Task1: Maintaining contact information of guests
Modify the storage structures of reservation records and implementations in your program, so
that it can store not only number of guests in each session but also contact information of
guests.
Task2: Add an additional item to your menu: Advanced Search
Search for guest record(s) in the list using the name or phone number, and print the full
details for the record(s). It can match word(s)/number within a string/number, and also print
multiple results. This is best explained by the following examples:
- If the full name “Paul J. Deitel” is stored inside the list, searching for either “Paul” or
“Deitel” should return the record.
- If the phone numbers “012-3214567”, “012-3314567”, and “012-3414567” are in the list,
then searching for “14567” must print all three records (because the number “14567”
occurs in all three phone numbers).
Note that you may need to use strstr() which allows you to locate substring.
Prepare the necessary data file(s) for building the data structure(s) needed in your application.
You may give additional assumptions for your application.
