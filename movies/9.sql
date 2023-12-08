SELECT name FROM people WHERE id IN
(SELECT person_id FROM stars WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2004 ) GROUP BY person_id HAVING COUNT(person_id) =1)
ORDER BY birth