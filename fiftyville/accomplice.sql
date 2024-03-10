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