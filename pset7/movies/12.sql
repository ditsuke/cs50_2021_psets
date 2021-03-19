SELECT movies.title FROM movies
JOIN stars ON stars.movie_id = movies.id
WHERE stars.person_id = (SELECT id FROM people WHERE name = "Johnny Depp")
AND movies.id IN (SELECT movie_id FROM stars WHERE person_id = 
(SELECT id FROM people WHERE name = "Helena Bonham Carter"));