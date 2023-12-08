-- Keep a log of any SQL queries you execute as you solve the mystery.

-- As suggested by the pset getting the crime scene reports on the given date, id of the crime recorded as '295'

SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND street = 'Humphrey Street';

-- as per the report crime took place at 10:15 ,3 witnesses were present and interviews were taken
-- it would make sense to view the bakery security logs next
-- below query is to determine who entered the baker before 10 15 am
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'entrance'
AND hour <=10 AND minute < 15

-- below query is to determine who left the bakery before 10 15 am
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour <=10 AND minute < 15
-- the license plates of the people present at the time of the theft are determined to be 4328GD8,R3G7486,13FNH73
-- getting the passport_number of people of the license plates                           (8496433585,7874488539,3642612721)

SELECT name FROM people
WHERE license_plate  = '4328GD8'
OR license_plate = 'R3G7486'
OR license_plate = '13FNH73';

SELECT * FROM interviews WHERE name IN
(SELECT name FROM people
WHERE license_plate  = '4328GD8'
OR license_plate = 'R3G7486'
OR license_plate = '13FNH73')

-- above info did not matter, looking at interviews on the day of the theft,looking at the transcripts of the 3 interviews
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- important info is
-- thief was at the ATM on 'Leggett Street' in the morning withdrawing some money x
-- thief talked to someone for less than a minute as he was about to leave the bakery
-- thief and his accomplice(lets call him kiki) were planning to leave on the earliest flight on 29th of july 2021 x
-- kiki is going to purchase the flight tickets
-- thief left the parking lot of the bakery withing 10 mins of the theft x

SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour =10 AND minute < 25 AND minute > 15

-- FROM the above query we get the list of all people who left in the time frame mentioned by the witness
-- getting the person id from the people table using the above license plate list

SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour =10 AND minute < 25 AND minute > 15);

-- getting the account number using the people(id)'s
SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour =10 AND minute < 25 AND minute > 15));

-- only 5 of the suspects have a bank account
-- atm transaction info of the 5 suspects on that day, only 4 of the suspects have have atm transactions as specified by the witness
SELECT account_number FROM atm_transactions
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
transaction_type = 'withdraw' AND
atm_location = 'Leggett Street' AND
account_number IN
(SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour =10 AND minute < 25 AND minute > 15)))

-- info the the 4 suspects
SELECT passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
transaction_type = 'withdraw' AND
atm_location = 'Leggett Street' AND
account_number IN
(SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour =10 AND minute < 25 AND minute > 15))))

-- earliest flight out of fiftyville on 29th july 2021 is( flight id is 36)
SELECT  *  FROM flights WHERE id = 36

-- passport numbers of all passengers on flight id 36
SELECT passport_number  FROM passengers WHERE flight_id = 36

-- info of the last 2 suspects
SELECT * FROM people
JOIN passengers on people.passport_number = passengers.passport_number
WHERE flight_id = 36 AND
passengers.passport_number IN
(SELECT passport_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
transaction_type = 'withdraw' AND
atm_location = 'Leggett Street' AND
account_number IN
(SELECT account_number FROM bank_accounts WHERE person_id IN
(SELECT id FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs
WHERE year = 2021 AND
month = 7 AND
day = 28 AND
activity = 'exit'
AND hour =10 AND minute < 25 AND minute > 15)))));

-- and cross checking phone call records from the day with duration less than 1 min with the info of the above 2 suspects
SELECT * FROM phone_calls
WHERE year = 2021 AND
month = 7 AND
day = 28 AND duration < 60


-- AND drum roll...... THE THIEF IS BRUCE
-- the phone no of accomplice is (375)555-8161
-- AND drum roll......... THE ACCOMPLICE IS mr robin

--one last drum roll for the city......... the city the thief escaped to is New York City


| 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
+-----+----------------+----------------+------+-------+-----+----------+