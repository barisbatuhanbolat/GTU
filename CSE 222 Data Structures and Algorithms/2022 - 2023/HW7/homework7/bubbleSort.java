package homework7;
/**
 * Class for bubbleSort algorithm
 * @author Barış Batuhan Bolat
 */
public class bubbleSort {
    private myMap originalMap;
    private myMap sortedMap;
    private String[] aux;
    /**
     * bubbleSort method
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
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j < n - i - 1; j++){
                if (values[j].getCount() > values[j + 1].getCount()) {
                    aux[0] = keys[j];

                    values[j] = values[j + 1];
                    keys[j] = keys[j + 1];

                    values[j + 1] = sortedMap.get(aux[0]);
                    keys[j + 1] = aux[0];
                }
            }
        }
        sortedMap.clearMap();
        for (int i = 0; i < keys.length; i++) {
            sortedMap.put(keys[i], values[i]);
        }
        return sortedMap;
    }
}
