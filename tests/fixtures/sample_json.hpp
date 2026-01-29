#pragma once
#include <nlohmann/json.hpp>

namespace test {
nlohmann::json data = R"({
  "store": {
    "name": "Example Store",
    "open": true,
    "location": {
      "country": "NG",
      "city": "Lagos",
      "coordinates": {
        "lat": 6.5244,
        "lon": 3.3792
      }
    },
    "books": [
      {
        "category": "reference",
        "author": "Nigel Rees",
        "title": "Sayings of the Century",
        "price": 8.95,
        "isbn": "0-553-21311-3",
        "available": true,
        "tags": ["quotes", "history"]
      },
      {
        "category": "fiction",
        "author": "Evelyn Waugh",
        "title": "Sword of Honour",
        "price": 12.99,
        "available": false,
        "tags": []
      },
      {
        "category": "fiction",
        "author": "Herman Melville",
        "title": "Moby Dick",
        "price": 8.99,
        "isbn": "0-553-21311-4",
        "available": true,
        "tags": ["classic", "whale"]
      }
    ],
    "bicycle": {
      "color": "red",
      "price": 19.95,
      "features": {
        "gears": 21,
        "electric": false,
        "extras": null
      }
    }
  },

  "users": [
    {
      "id": 1,
      "name": "Alice",
      "age": 30,
      "active": true,
      "roles": ["admin", "editor"],
      "address": {
        "city": "Abuja",
        "zip": "900001"
      }
    },
    {
      "id": 2,
      "name": "Bob",
      "age": 22,
      "active": false,
      "roles": ["viewer"],
      "address": {
        "city": "Lagos",
        "zip": null
      }
    }
  ],

  "orders": [
    {
      "id": "ORD-001",
      "userId": 1,
      "total": 29.94,
      "items": [
        { "sku": "BOOK-001", "qty": 2, "price": 8.95 },
        { "sku": "BIKE-001", "qty": 1, "price": 19.95 }
      ],
      "status": "paid"
    },
    {
      "id": "ORD-002",
      "userId": 2,
      "total": 0,
      "items": [],
      "status": "cancelled"
    }
  ],

  "metadata": {
    "generatedAt": "2026-01-27T10:00:00Z",
    "version": 1,
    "flags": {
      "experimental": true,
      "deprecated": false
    }
  }
})"_json;
}