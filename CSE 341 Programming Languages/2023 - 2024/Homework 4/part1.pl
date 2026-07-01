% Delivery personnel with ID, capacity to carry, work hours, current job, and current location
deliveryPerson(1, 10, 8, none, 'Admin Office').
deliveryPerson(2, 15, 12, none, 'Library').
deliveryPerson(3, 20, 16, job5,'Engineering Bld.').

% Places with unique ID
place('Admin Office').
place('Engineering Bld.').
place('Lecture Hall A').
place('Library').
place('Institute Y').
place('Cafeteria').
place('Social Sciences Bld.').
place('Institute X').

% Objects with ID , weight , pickup place , drop off place , urgency , delivery person ID if in transit 
object(job1 ,5 ,'Admin Office' ,'Library', medium ,none).
object(job2 ,7 ,'Engineering Bld.' ,'Cafeteria', low ,none).
object(job3 ,10,'Lecture Hall A','Social Sciences Bld.', high ,none).
object(job4 ,12,'Library','Institute X', medium ,none).
object(job5 ,8 ,'Cafeteria','Engineering Bld.', low ,(3)).

% Map routes between places and time to travel
route('Admin Office', 'Engineering Bld.', 3).
route('Engineering Bld.', 'Admin Office', 3).

route('Admin Office', 'Library', 1).
route('Library', 'Admin Office', 1).

route('Admin Office', 'Cafeteria', 4).
route('Cafeteria', 'Admin Office', 4).

route('Engineering Bld.', 'Lecture Hall A', 2).
route('Lecture Hall A', 'Engineering Bld.', 2).

route('Engineering Bld.', 'Library', 5).
route('Library', 'Engineering Bld.', 5).

route('Lecture Hall A', 'Institute Y', 3).
route('Institute Y', 'Lecture Hall A', 3).

route('Institute Y', 'Library', 3).
route('Library', 'Institute Y', 3).

route('Library', 'Cafeteria', 5).
route('Cafeteria', 'Library', 5).

route('Library', 'Social Sciences Bld.', 2).
route('Social Sciences Bld.', 'Library', 2).

route('Cafeteria', 'Social Sciences Bld.', 2).
route('Social Sciences Bld.', 'Cafeteria', 2).

route('Social Sciences Bld.', 'Institute X', 8).
route('Institute X', 'Social Sciences Bld.', 8).


% Find the shortest path between two places using Dijkstra’s algorithm 
shortestPath(Start, End, Path, Time) :- 
    dijkstra([0-Start], End, [Start], RevPath, Time), 
    reverse(RevPath, Path).

% Base case
dijkstra([Time-End|_], End, Visited, [End|Visited], Time).

% Recursive case
dijkstra([Time-Place|Rest], End, Visited, Path, TotalTime) :- 
    findall(T-New, (route(Place, New, T), not(member(New, Visited))), Neighbors), 
    maplist(incrementTime(Time), Neighbors, Updated), 
    append(Rest, Updated, Queue), sort(Queue, Sorted), 
    dijkstra(Sorted, End, [Place|Visited], Path, TotalTime).

% Add time to a place 
incrementTime(Time, T-New, Time1-New) :- 
    Time1 is Time + T.

% Check if delivery person is available for a given object 
canDeliver(PersonID,ObjectID):- 
    object(ObjectID,_Weight,_PickupPlace,_DropoffPlace,_Urgency,(PersonID)), 
    format('Delivery person ~w is already delivering the object.' , [PersonID]).
canDeliver(PersonID,ObjectID):- 
    deliveryPerson(PersonID,Capacity,_WorkHours,None,CurrentLocation), 
    None == none, 
    object(ObjectID,ObjectWeight,PickupPlace,DropoffPlace,_Urgency,None), 
    ObjectWeight =< Capacity, 
    shortestPath(CurrentLocation,PickupPlace,_PickupPath,PickupTime), 
    shortestPath(PickupPlace,DropoffPlace,_DropoffPath,DropoffTime), 
    TotalTime is PickupTime + DropoffTime, 
    format('Delivery person with ID: ~w can deliver the object in ~w hours.', [PersonID, TotalTime]).