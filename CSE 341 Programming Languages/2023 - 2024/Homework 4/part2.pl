% Rules for classifying Iris flowers based on sepal and petal measurements
classify(Sepal_Length, Sepal_Width, Petal_Length, Petal_Width, Class) :-
    (
        Petal_Length =< 2.45,
        Class = 'Iris-setosa'
    );
    (
        Petal_Length > 2.45, Petal_Length =< 4.75, Petal_Width =< 1.65,
        Class = 'Iris-versicolor'
    );
    (
        Petal_Length > 2.45, Petal_Length =< 4.75, Petal_Width > 1.65,
        Class = 'Iris-virginica'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width =< 1.75, Petal_Length =< 4.95,
        Class = 'Iris-versicolor'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width =< 1.75, Petal_Length > 4.95, Petal_Width =< 1.55,
        Class = 'Iris-virginica'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width =< 1.75, Petal_Length > 4.95, Petal_Width > 1.55, Sepal_Length =< 6.95,
        Class = 'Iris-versicolor'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width =< 1.75, Petal_Length > 4.95, Petal_Width > 1.55, Sepal_Length > 6.95,
        Class = 'Iris-virginica'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width > 1.75, Petal_Length =< 4.85, Sepal_Width =< 3.10,
        Class = 'Iris-virginica'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width > 1.75, Petal_Length =< 4.85, Sepal_Width > 3.10,
        Class = 'Iris-versicolor'
    );
    (
        Petal_Length > 2.45, Petal_Length > 4.75, Petal_Width > 1.75, Petal_Length > 4.85,
        Class = 'Iris-virginica'
    ).

% Responding to queries
classify(Sepal_Length, Sepal_Width, Petal_Length, Petal_Width) :-
    classify(Sepal_Length, Sepal_Width, Petal_Length, Petal_Width, Class),
    format('Yes: ~w', [Class]).
