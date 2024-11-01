package homework7;
/**
 * Class for quickSort algorithm
 * @author Barış Batuhan Bolat
 */
public class quickSort {
    private myMap originalMap;
    private myMap sortedMap;
    private String[] aux;
    /**
     * quickSort method
     * @param map myMap object to be sorted
     * @return Sorted Map
     */
    public myMap sort(myMap map) {
        originalMap = map;
        sortedMap = new myMap();
        sortedMap.setMap(originalMap.getMap());
        sortedMap.setSize(originalMap.getSize());
        sortedMap.setStr(originalMap.getstr());

        String[] keys = sortedMap.getKeys();
        info[] values = sortedMap.getValues();
        aux = new String[1];
        int n = sortedMap.getSize();

        sortHelper(keys,values, 0, n - 1);

        sortedMap.clearMap();
        for (int i = 0; i < keys.length; i++) {
            sortedMap.put(keys[i], values[i]);
        }
        return sortedMap;
    }
    /**
     * Recursive helper method for quickSort
     * @param keys Array of keys of map
     * @param values Array of values of map
     * @param start Begining index of key array and value array
     * @param end Last index of key array and value array
     */
    private void sortHelper(String[] keys, info[] values, int start, int end) {
        if (start < end) {
            aux = new String[1];
            int pivot = values[end].getCount();
            int i = start - 1;
            for (int j = start; j < end; j++) {
                if (values[j].getCount() < pivot) {
                    i++;
                    aux[0] = keys[i];
                    keys[i] = keys[j];
                    keys[j] = aux[0];
    
                    values[i] = values[j];
                    values[j] = sortedMap.get(aux[0]);  
                }
            }
            aux[0] = keys[i + 1];
            keys[i + 1] = keys[end];
            keys[end] = aux[0];
    
            values[i+1] = values[end];
            values[end] = sortedMap.get(aux[0]); 

            int pivotIndex = i + 1;
            sortHelper(keys, values, start, pivotIndex - 1);
            sortHelper(keys, values, pivotIndex + 1, end);
        }
    }
}

