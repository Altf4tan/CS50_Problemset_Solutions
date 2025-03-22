--In 12.sql, write a SQL query to list the titles of all movies
--in which both Bradley Cooper and Jennifer Lawrence starred.
SELECT movies.title
FROM movies
WHERE movies.id IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        SELECT id
        FROM people
        WHERE name = 'Bradley Cooper'
    )
)
AND movies.id IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        SELECT id
        FROM people
        WHERE name = 'Jennifer Lawrence'
    )
);
