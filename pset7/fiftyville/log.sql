/* Keep a log of any SQL queries you execute as you solve the mystery.
 Get witness reports from place and time of Duck theft */
--
--
/* GET CRIME SCENE REPORTS */
SELECT year,
    month,
    day,
    description
FROM crime_scene_reports
WHERE street = "Chamberlin Street"
    AND day = "28"
    AND month = "7";
--
/* PEOPLE EXITING COURTHOUSE WITHIN 10 MINUTES OF CRIME ON CAR */
SELECT people.id,
    people.name
FROM courthouse_security_logs
    JOIN people ON courthouse_security_logs.license_plate = people.license_plate
WHERE year = "2020"
    AND month = "7"
    AND day = "28"
    AND activity = "exit"
    AND hour = "10"
    AND minute >= "15"
    AND minute <= "25"
ORDER BY hour,
    minute;
--
/* GET PEOPLE WHO TOOK THE EARLIEST FLIGHT FROM FIFTYVILLE (ON THE 28th OR NEXT DAY)
 * AND ALSO DROVE OUT OF THE COURTROOM 
 */
SELECT people.id,
    people.name
FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON airports.id = flights.origin_airport_id
    OR airports.id = flights.destination_airport_id
WHERE passengers.passport_number IN (
        SELECT passport_number
        FROM people
        WHERE license_plate IN (
                SELECT license_plate
                FROM courthouse_security_logs
                WHERE year = "2020"
                    AND month = "7"
                    AND day = "28"
                    AND activity = "exit"
                    AND hour = "10"
                    AND minute > "15"
            )
    )
    AND flights.origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE full_name LIKE "Fiftyville%"
    )
    AND flights.id = (
        SELECT id
        FROM flights
        WHERE year = "2020"
            AND month = "7"
            AND day = "29"
        ORDER BY day,
            hour,
            minute
        LIMIT 1
    )
ORDER BY flights.day,
    flights.hour,
    flights.minute;
--
/* GET NAMES OF PEOPLE WHO ALSO WITHDREW AT THE FIFER STT ATM ON THE MORNING OF 28TH */
SELECT people.id,
    people.name
FROM people
    JOIN bank_accounts ON bank_accounts.person_id = people.id
    JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE year = 2020
    AND month = "7"
    AND day = "28"
    AND transaction_type = "withdraw"
    AND atm_location = "Fifer Street";
--
/* GET PEOPLE WHO MADE PHONE CALLS OF LESS THAN 60s that morning */
SELECT people.id,
    people.name
FROM phone_calls
    JOIN people ON people.phone_number = phone_calls.caller
WHERE duration < "60"
    AND year = "2020"
    AND month = "7"
    AND day = "28";
--
/* CHECK FOR INTERSECTION OF ABOVE SETS
 */
SELECT people.id,
    people.name
FROM phone_calls
    JOIN people ON people.phone_number = phone_calls.caller
WHERE duration < "60"
    AND year = "2020"
    AND month = "7"
    AND day = "28"
    AND people.id IN (
        -- person should've made atm withdrawal at fifer str. that morning
        SELECT people.id
        FROM people
            JOIN bank_accounts ON bank_accounts.person_id = people.id
            JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
        WHERE year = 2020
            AND month = "7"
            AND day = "28"
            AND transaction_type = "withdraw"
            AND atm_location = "Fifer Street"
    )
INTERSECT
-- intersect with people who exited courthouse and took flight as per witness reports
SELECT people.id,
    people.name
FROM people
    JOIN passengers ON passengers.passport_number = people.passport_number
    JOIN flights ON flights.id = passengers.flight_id
    JOIN airports ON airports.id = flights.origin_airport_id
    OR airports.id = flights.destination_airport_id
WHERE passengers.passport_number IN (
        SELECT passport_number
        FROM people
        WHERE license_plate IN (
                SELECT license_plate
                FROM courthouse_security_logs
                WHERE year = "2020"
                    AND month = "7"
                    AND day = "28"
                    AND activity = "exit"
                    AND hour = "10"
                    AND minute >= "15"
                    AND minute <= "25"
            )
    )
    AND flights.id = (
        SELECT id
        FROM flights
        WHERE year = "2020"
            AND month = "7"
            AND day = "29"
            AND origin_airport_id = (
                SELECT id
                FROM airports
                WHERE full_name LIKE "Fiftyville%"
            )
        ORDER BY day,
            hour,
            minute
        LIMIT 1
    )
    /* INTERSECTION FOUND! Ernest (686048) is the culprit */
    --
    /* FIND ACCOMPLICE */
SELECT people.id,
    people.name
FROM people
    JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.duration < "60"
    AND phone_calls.year = "2020"
    AND phone_calls.month = "7"
    AND phone_calls.day = "28"
    AND phone_calls.caller = (
        SELECT phone_number
        FROM people
        WHERE id = "686048"
    );
-- MATCH FOUND! Berthold (864400)
/* FIND Location thief escaped to*/
SELECT airports.city
FROM flights
    JOIN airports ON airports.id = flights.destination_airport_id
WHERE year = "2020"
    AND month = "7"
    AND day = "29"
    AND origin_airport_id = (
        SELECT id
        FROM airports
        WHERE full_name LIKE "Fiftyville%"
    )
ORDER BY day,
    hour,
    minute
LIMIT 1 - - MATCH FOUND ! -->London