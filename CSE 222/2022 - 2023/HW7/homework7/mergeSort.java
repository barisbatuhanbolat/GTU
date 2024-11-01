package homework7;
/**
 * Class for mergeSort algorithm
 * @author Barış Batuhan Bolat
 */

public class mergeSort {
    private myMap originalMap;
    private myMap sortedMap;
    private String[] aux;
    /**
     * MergeSort method
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
        sortHelper(keys, values, 0, keys.length - 1);
        sortedMap.clearMap();
        for (int i = 0; i < keys.length; i++) {
            sortedMap.put(keys[i], values[i]);
        }
        return sortedMap;
    }
    /**
     * Recursive helper method for mergesort
     * @param keys Array of keys of map
     * @param values Array of values of map
     * @param l Begining index of key array and value array
     * @param r Last index of key array and value array
     */
    private void sortHelper(String[] keys, info[] values, int l, int r) {
        if(l<r){
            int m = (l + r) / 2;
            sortHelper(keys, values, l, m);
            sortHelper(keys, values, m + 1, r);
            merge(keys, values, l, m, r);
        }
    }
    /**
     * Merges two subarrays of keys and values
     * @param keys Array of keys of map
     * @param values Array of values of map
     * @param l Begining index of key array and value array
     * @param m Middle indef of key array and value array
     * @param r Last index of key array and value array
     */
    private void merge(String[] keys, info[] values, int l, int m, int r) {
        aux = new String[r - l + 1];
        int i = l;
        int j = m + 1;
        int k = 0;

        while (i <= m && j <= r) {
            if (values[i].getCount() <= values[j].getCount()) {
                aux[k] = keys[i];
                sortedMap.get(aux[k]).set(values[i]);
                i++;
            } 
            else {
                aux[k] = keys[j];
                sortedMap.get(aux[k]).set(values[j]);
                j++;
            }
            k++;
        }
        while (i <= m) {
            aux[k] = keys[i];
            sortedMap.get(aux[k]).set(values[i]);
            i++;
            k++;
        }
        while (j <= r) {
            aux[k] = keys[j];
            sortedMap.get(aux[k]).set(values[j]);
            j++;
            k++;
        }
        for (i = 0; i < aux.length; i++) {
            keys[l + i] = aux[i];
            values[l + i] = sortedMap.get(aux[i]);
        }
    }
}
