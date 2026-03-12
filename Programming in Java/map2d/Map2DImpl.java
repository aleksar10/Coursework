import java.util.Map;
import java.util.HashMap;
import java.util.function.Function;

public class Map2DImpl<R, C, V> implements Map2D<R, C, V> {
    private Map<R, Map<C, V>> map;

    public Map2DImpl() {
        map = new HashMap<>();
    }

    @Override
    public V put(R rowKey, C columnKey, V value) {
        if (rowKey == null || columnKey == null)
            throw new NullPointerException();
        
        Map<C,V> row = map.get(rowKey);
        
        if (row == null) {
            row = new HashMap<>();
            map.put(rowKey, row);
        }
        return row.put(columnKey, value);
    }

    @Override
    public V get(R rowKey, C columnKey) {
        return getOrDefault(rowKey, columnKey, null);
    }

    @Override
    public V getOrDefault(R rowKey, C columnKey, V defaultValue) {
        Map<C,V> row = map.get(rowKey);

        if (row == null)
            return defaultValue;
        else 
            return row.getOrDefault(columnKey, defaultValue);
    }

    @Override
    public V remove(R rowKey, C columnKey) {
        Map<C,V> row = map.get(rowKey);
        if (row == null)
            return null;
        
        V removed = row.remove(columnKey);
        if (row.isEmpty())
            map.remove(rowKey);

        return removed;
    }

    @Override
    public boolean isEmpty() {
        return map.isEmpty();
    }

    @Override
    public boolean nonEmpty() {
        return !map.isEmpty();
    }

    @Override
    public int size() {
        int valuesCount = 0;

        for (Map<C,V> row : map.values())
            valuesCount += row.size();
        
        return valuesCount;
    }

    @Override
    public void clear() {
        map.clear();
    }

    @Override
    public Map<C, V> rowView(R rowKey) {
        Map<C, V> row = map.get(rowKey);

        if (row == null) 
            return Map.copyOf(new HashMap<>());
        else
            return Map.copyOf(row);
    }

    @Override
    public Map<R, V> columnView(C columnKey) {
        Map<R, V> column = new HashMap<>();

        for (R rowKey : map.keySet()) {
            Map<C,V> row = map.get(rowKey);

            if (row.containsKey(columnKey)) {
                V value = row.get(columnKey);
                column.put(rowKey, value);
            }
        }
        return Map.copyOf(column);
    }

    @Override
    public boolean containsValue(V value) {
        for (Map<C, V> row : map.values()) {
            if (row.containsValue(value))
                return true;
        }
        return false;
    }

    @Override
    public boolean containsKey(R rowKey, C columnKey) {
        Map<C,V> row = map.get(rowKey);
        
        if (row != null)
            return row.containsKey(columnKey);

        return false;
    }

    @Override
    public boolean containsRow(R rowKey) {
        return map.containsKey(rowKey);
    }

    @Override
    public boolean containsColumn(C columnKey) {
        for (Map<C, V> row : map.values()) {
            if (row.containsKey(columnKey))
                return true;
        }
        return false;
    }

    @Override
    public Map<R, Map<C,V>> rowMapView() {
        Map<R, Map<C,V>> rowMap = new HashMap<>();

        for (R rowKey : map.keySet()) 
            rowMap.put(rowKey, rowView(rowKey));

        return Map.copyOf(rowMap);
    }

    @Override
    public Map<C, Map<R,V>> columnMapView() {
        Map<C, Map<R, V>> columnMap = new HashMap<>();

        for (Map<C, V> row : map.values()) {
            for (C columnKey : row.keySet()) {
                if (!columnMap.containsKey(columnKey)) 
                    columnMap.put(columnKey, columnView(columnKey)); 
            }
        }
        return Map.copyOf(columnMap);
    }

    @Override
    public Map2D<R, C, V> fillMapFromRow(Map<? super C, ? super V> target, R rowKey) {
        Map<C, V> row = map.get(rowKey);
        if (row != null) 
            target.putAll(row);
        
        return this;
    }

    @Override
    public Map2D<R, C, V> fillMapFromColumn(Map<? super R, ? super V> target, C columnKey) {
        for (R rowKey : map.keySet()) {
            Map<C, V> row = map.get(rowKey);
            
            if (row.containsKey(columnKey)) 
                target.put(rowKey, row.get(columnKey));
        }
        return this;
    }

    @Override
    public Map2D<R, C, V> putAll(Map2D<? extends R, ? extends C, ? extends V> source) {
        for (R rowKey : source.rowMapView().keySet()) {
            Map<? extends C, ? extends V> row = source.rowMapView().get(rowKey);

            for (C columnKey : row.keySet()) 
                put(rowKey, columnKey, row.get(columnKey));
        }
        return this;
    }

    @Override
    public Map2D<R, C, V> putAllToRow(Map<? extends C, ? extends V> source, R rowKey){
        for (C columnKey : source.keySet()) 
            put(rowKey, columnKey, source.get(columnKey));
   
        return this;
    }

    @Override
    public Map2D<R, C, V> putAllToColumn(Map<? extends R, ? extends V> source, C columnKey) {
        for (R rowKey : source.keySet())
            put(rowKey, columnKey, source.get(rowKey));

        return this;
    }

    @Override
    public <R2, C2, V2> Map2D<R2, C2, V2> copyWithConversion(
            Function<? super R, ? extends R2> rowFunction,
            Function<? super C, ? extends C2> columnFunction,
            Function<? super V, ? extends V2> valueFunction) {

        Map2D<R2, C2, V2> copy = Map2D.createInstance();

        for (R rowKey : map.keySet()) {
            R2 newRow = rowFunction.apply(rowKey);
            Map<C, V> row = map.get(rowKey);

            for (C columnKey : row.keySet()) {
                C2 newColumn = columnFunction.apply(columnKey);
                V2 newValue = valueFunction.apply(row.get(columnKey));
                copy.put(newRow, newColumn, newValue);
            }
        }
        return copy;
    }
}
