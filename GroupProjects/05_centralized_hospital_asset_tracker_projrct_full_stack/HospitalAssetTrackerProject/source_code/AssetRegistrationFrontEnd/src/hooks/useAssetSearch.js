/**
 * @file useAssetSearch.js
 * @author Farros Ramzy (you@domain.com)
 * @description 
 * @version 1.0.0
 * @date 2026-05-08

 * @Copyright (c) 2026
 */


import { useMemo, useState } from "react";

export function useAssetSearch(assets = []) {
  const [searchTerm, setSearchTerm] = useState("");

  const filteredAssets = useMemo(() => {
    const query = searchTerm.trim().toLowerCase();

    if (!query) {
      return assets;
    }

    return assets.filter((asset) => {
      const searchableText = [
        asset.tag_id,
        asset.item_name,
        asset.status,
        asset.last_location,
        asset.last_room_name,
        asset.hospital_name,
        asset.last_seen_at,
      ]
        .filter(Boolean)
        .join(" ")
        .toLowerCase();

      return searchableText.includes(query);
    });
  }, [assets, searchTerm]);

  return {
    searchTerm,
    setSearchTerm,
    filteredAssets,
  };
}