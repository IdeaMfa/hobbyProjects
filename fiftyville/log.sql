-- Keep a log of any SQL queries you execute as you solve the mystery.
-- To see the descriptions of crime scene report at that day
SELECT id, description
    FROM crime_scene_reports
    WHERE day = 28
    AND month = 7
    AND street = 'Humphrey Street';

-- To see the corrresonding interviews
SELECT transcript
    FROM interviews
    WHERE year = 2021
    AND day = 28
    AND month = 7;

-- To understand phone_call table
SELECT caller, receiver, duration
    FROM phone_calls
    WHERE day = 28
    AND month = 7
    AND duration < 60;

-- To understand bakery_security_logs table
SELECT activity, license_plate
    FROM bakery_security_logs
    WHERE year = 2021
    AND day = 28
    AND month = 7
    AND hour = 10
    AND minute >= 15
    AND minute < 25;

-- To see the time of flights
SELECT hour, minute
    FROM flights
    WHERE origin_airport_id = (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    ORDER BY hour, minute;


-- To pull the name from the datas I've got from the other querys
SELECT name
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2021
            AND day = 28
            AND month = 7
            AND hour = 10
            AND minute >= 15
            AND minute < 25
            AND activity = 'exit'
    )
    AND phone_number IN (
        SELECT caller
            FROM phone_calls
            WHERE day = 28
            AND month = 7
            AND year = 2021
            AND duration < 60
    )
    AND passport_number IN (
        SELECT passport_number
            FROM passengers
            WHERE flight_id IN (
                SELECT id
                    FROM flights
                        WHERE day = 29
                        AND month = 7
                        AND year = 2021
                        AND hour <= 8
                        AND origin_airport_id = (
                            SELECT id
                                FROM airports
                                WHERE city = 'Fiftyville'
                        )
            )
    )
    AND id IN (
        SELECT person_id
            FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number
                    FROM atm_transactions
                    WHERE month = 7
                    AND day = 28
                    AND year = 2021
                    AND transaction_type = 'withdraw'
            )
    );

-- To see who the accomplice is
SELECT name
    FROM people
    WHERE phone_number = (
        SELECT receiver
            FROM phone_calls
            WHERE day = 28
            AND month = 7
            AND year = 2021
            AND duration < 60
            AND caller = (
                SELECT phone_number
                    FROM people
                    WHERE name = 'Bruce'
            )
    );

-- To see where the thief escape to, and I've learned that
-- the thief's flight started at 8
SELECT city
    FROM airports
    WHERE id = (
        SELECT destination_airport_id
            FROM flights
            WHERE origin_airport_id = (
                SELECT id
                    FROM airports
                    WHERE city = 'Fiftyville'
            )
            AND day = 29
            AND month = 7
            AND year = 2021
            AND hour = 8
    );