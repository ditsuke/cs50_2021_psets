SELECT DISTINCT name 
FROM stars
INNER JOIN people ON stars.person_id = people.id
WHERE stars.movie_id = (SELECT id FROM movies WHERE title = "Toy Story");