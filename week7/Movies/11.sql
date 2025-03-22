--select titles
SELECT movies.title
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE movies.id IN
(
    --select person ID
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        --select Chadwick Bosemans id
        SELECT id
        FROM people
        WHERE name = 'Chadwick Boseman'
    )
)
ORDER BY ratings.rating DESC
LIMIT 5;
