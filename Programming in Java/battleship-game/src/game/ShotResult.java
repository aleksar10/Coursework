package game;

public enum ShotResult {
    MISS,
    HIT,
    SUNK,
    LAST_SUNK;

    public String toString() {
        return switch(this) {
            case MISS -> "miss";
            case HIT -> "hit";
            case SUNK -> "hit and sunk";
            case LAST_SUNK -> "last sunk";
        };
    }

    public static ShotResult fromString(String s) {
        return switch (s) {
            case "miss" -> MISS;
            case "hit" -> HIT;
            case "hit and sunk" -> SUNK;
            case "last sunk" -> LAST_SUNK;
            default -> throw new IllegalArgumentException("Unknown shot result: " + s);
        };
    }
}