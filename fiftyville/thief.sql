-- to see who the thief is
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