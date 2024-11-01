package homework7;
/**
 * Class for insertionSort algorithm
 * @author Barış Batuhan Bolat
 */
public class insertionSort {
    private myMap originalMap;
    private myMap sortedMap;
    private String[] aux;

    /**
     * insertionSort method
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
        for (int i = 1; i < n; ++i) {
            aux[0] = keys[i];
            int j = i - 1;
 
            while (j >= 0 && values[j].getCount() > sortedMap.get(aux[0]).getCount()) {
                keys[j + 1] = keys[j];
                values[j + 1] = values[j];
                j = j - 1;
            }
            keys[j + 1] = aux[0];
            values[j + 1] = sortedMap.get(aux[0]);
        }
        sortedMap.clearMap();
        for (int i = 0; i < keys.length; i++) {
            sortedMap.put(keys[i], values[i]);
        }
        return sortedMap;
    }
}
