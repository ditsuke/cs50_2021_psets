SELECT people.name FROM people WHERE people.id IN (SELECT DISTINCT people.id FROM people
INNER JOIN directors ON directors.person_id = people.id
INNER JOIN movies ON movies.id = directors.movie_id
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= "9.0");