package homework7;
/**
 * Class for selectionSort algorithm
 * @author Barış Batuhan Bolat
 */
public class selectionSort {
    private myMap originalMap;
    private myMap sortedMap;
    private String[] aux;
    /**
     * selectionSort method
     * @param map myMap object to be sorted
     * @return Sorted Map
     */
    public myMap sort(myMap map){
        originalMap = map;
        sortedMap = new myMap();
        sortedMap.setMap(originalMap.getMap());
        sortedMap.setSize(originalMap.getSize());
        sortedMap.setStr(originalMap.getstr());

        String[] keys = sortedMap.getKeys();
        info[] values = sortedMap.getValues();
        aux = new String[1];
        int n = sortedMap.getSize();
        for (int i = 0; i < n-1; i++)
        {
            int min = i;
            for (int j = i+1; j < n; j++){
                if (values[j].getCount() < values[min].getCount()){
                    min = j;
                }
            }
            aux[0] = keys[min];

            values[min] = values[i];
            values[i] = sortedMap.get(aux[0]);

            keys[min] = keys[i];
            keys[i] = aux[0];
        }
        sortedMap.clearMap();
        for (int i = 0; i < keys.length; i++) {
            sortedMap.put(keys[i], values[i]);
        }
        return sortedMap;        
    }
}