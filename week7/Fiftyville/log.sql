-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE description LIKE '%duck%';
--Theft took place at 10:15 am 28 July at Humphrey Street Bakery
SELECT * FROM bakery_security_logs WHERE hour = 10 AND minute = 15;
--Suspect have 11J91FW license plate
SELECT * FROM people WHERE license_place = '11J91FW';
--Suspects actual name is Noah
--Phone number is (959) 555-4871
--Passport number 1095374669
--ID 375525
SELECT * FROM interviews WHERE name = 'Noah';
--Talking about some land in new zealand that left to him by his uncle Ned
--He talks about that he cannot get lands money but only the interest rate
--Probably headed to new zealand, auckland from airport
SELECT * FROM phone_calls WHERE caller LIKE '%4871%';
--Made 3 phone calls 1 before and 2 after the crime day, each call with diffirent receiver
--Probably planned this with someone before crime, reached out 2 different people to what do with duck after
--007 555 2874, 357 555 0246, 839 555-1757
SELECT * FROM people WHERE phone_number LIKE '%2874%';
--Second suspect that has been called before crime
--ID: 282425, Name: Martha, Passport Number = NULL, license_plate = O784M2U
SELECT * FROM people WHERE phone_number LIKE '%0246%';
--Third suspect that has been called after crime
--ID: 572028, Name: Paul, Passport Number: 9143726159, License Plate: R64E41W
SELECT * FROM people WHERE phone_number LIKE '%1757%';
--Fourth suspect that has been called upon after third
--ID: 506435, Name: Zachary, Passport Number: NULL, License Plate: 5810O6V
SELECT * FROM bakery_security_logs WHERE license_plate = 'O784M2U';
--Second suspect Martha was in bakery from 12:23 PM to 4:51 PM at 26 July 2024
--Second suspect Martha was in bakery from 8:59 AM to 8:59 AM at 28 July 2024
SELECT * FROM bakery_security_logs WHERE license_plate = '5810O6V';
--Fourth suspect Zachary was in bakery from 10:49 AM to 13:37 PM at 25 July 2024
--Okay so I was wrong, Noah was not the thief, I should've read crime scene reports more carefully
--there was appearantly 10 minute time frame between 10:15 am and 10:25 am which crime took place in
--and thief was withrawing money from ATM on Leggett Street earlier that morning
--Also thief made a phone call just after the theft, mentioning 'Taking the earliest flight from fiftyville next day'
--asked the person on phone to buy a flight ticket
SELECT license_plate FROM bakery_security_logs WHERE year = 2024
AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25
AND activity = 'exit';
--License plates of our main suspects:
--5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55
SELECT * FROM atm_transactions WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';
--Account numbers of our suspects:
--28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199
SELECT name FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN (28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199);
--Main suspect names: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
SELECT caller, receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;
--Main and second suspect phone numbers which had less than <60 duration on phone
--|     caller     |    receiver    |
--| (367) 555-5533 | (375) 555-8161 | => Bruce's phone number is caller, Robin is receiver
--| (286) 555-6063 | (676) 555-6554 | => Taylor's phone number is caller, James is receiver
--| (770) 555-1861 | (725) 555-3243 | => Diana's phone number is caller, Philip is receiver
--| (826) 555-1652 | (066) 555-9701 | => Kenny's phone number is caller, Doris is receiver
--| (338) 555-6650 | (704) 555-2131 | => Benista's phone number is caller, Anna is receiver
SELECT * FROM people WHERE license_plate = '94KL13X';
--Bruce's car was at bakery in crime time frame
--Bruce made a call which had duration less than 60 seconds in crime day
--Bruce's account number was associated with Leggett Street atm withdrawals
SELECT * FROM people WHERE license_plate = '4328GD8';
--Luca was at bakery during crime day
--Luca did not made a call on that day however he made a withdrawal from account yet that does not make Luca our thief
SELECT * FROM people WHERE license_plate = 'L93JTIZ';
--Iman was at bakery and also made a withdrawal yet he didnt made any call within our suspect range
SELECT * FROM people WHERE license_plate = '322W7JE';
--Diana's car was at bakery in crime time frame
--Diana made a call which had duration less than 60 seconds in crime day
--Diana's account number was associated with Leggett Street atm withdrawals
--So that makes our suspect number 4
--Bruce and Robin
--Diana and Philip
SELECT * FROM people WHERE name = 'Bruce' OR name = 'Diana';
--Okay so we have passport numbers of both Bruce and Diana
--Bruce: 5773159633, Diana: 3592750733
--All that is left to do is find out whether they used a flight or not
 SELECT * FROM flights WHERE year = 2024 AND month = 7 AND day = 29;
--Thief took the earliest flight out of Fiftyville on July 29
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--| 18 | 8                 | 6                      | 2024 | 7     | 29  | 16   | 0      |
--| 23 | 8                 | 11                     | 2024 | 7     | 29  | 12   | 15     |
--| 36 | 8                 | 4                      | 2024 | 7     | 29  | 8    | 20     | => Earliest flight that day
--| 43 | 8                 | 1                      | 2024 | 7     | 29  | 9    | 30     |
--| 53 | 8                 | 9                      | 2024 | 7     | 29  | 15   | 20     |
SELECT city FROM airports WHERE id = 4;
--We found out that thief escaped to New York City at 29 July 8:20 AM from Fiftyville airport
SELECT * FROM passengers WHERE flight_id = 36;
--We have found out that Bruce was on this flight as his passport number shown in the list
--with him having the seat of 4A
--There is no evidence of Diana taking this flight as her passport number was missing on the list
--proving that our main suspect is Bruce himself along with his accomplice Robin
--perpetuated the duck thievery
--Alas, we still have to prove Robin is deeply involved with the case itself
--phone call to our main suspect on the day of crime is not enough evidence for robin
--to be accused of this crime
SELECT * FROM people WHERE name = 'Robin';
--We have found out that Robin's license plate is 4V16VO0
--His id is 864400, phone number is already known from the queries above
