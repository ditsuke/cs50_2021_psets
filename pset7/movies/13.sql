SELECT name FROM people 
WHERE id IN (SELECT DISTINCT person_id FROM stars 
WHERE stars.movie_id 
IN (SELECT id FROM movies WHERE id IN 
(SELECT movie_id FROM stars WHERE person_id = 
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = "1958")))
AND stars.person_id !=
(SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = "1958"));