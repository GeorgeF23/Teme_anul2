package com.george;

import java.time.LocalDateTime;

public class Discount {
    private String name;
    private DiscountType discountType;
    private double value;
    private LocalDateTime lastDateApplied = null;
}
