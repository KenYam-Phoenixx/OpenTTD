/* $Id$ */

/** @file waypoint.h Base of waypoints. */

#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "waypoint_type.h"
#include "rail_map.h"
#include "command_type.h"
#include "station_base.h"
#include "town_type.h"
#include "viewport_type.h"
#include "date_type.h"
#include "core/pool_type.hpp"

typedef Pool<Waypoint, WaypointID, 32, 64000> WaypointPool;
extern WaypointPool _waypoint_pool;

struct Waypoint : WaypointPool::PoolItem<&_waypoint_pool> {
	TileIndex xy;      ///< Tile of waypoint

	Town *town;        ///< Town associated with the waypoint
	uint16 town_cn;    ///< The Nth waypoint for this town (consecutive number)
	char *name;        ///< Custom name. If not set, town + town_cn is used for naming

	ViewportSign sign; ///< Dimensions of sign (not saved)
	Date build_date;   ///< Date of construction
	OwnerByte owner;   ///< Whom this waypoint belongs to

	StationSpecList spec; ///< NewGRF specification of the station

	byte delete_ctr;   ///< Delete counter. If greater than 0 then it is decremented until it reaches 0; the waypoint is then is deleted.

	Waypoint(TileIndex tile = INVALID_TILE) : xy(tile) { }
	~Waypoint();

	void UpdateVirtCoord();

	void AssignStationSpec(uint index);
};

#define FOR_ALL_WAYPOINTS_FROM(var, start) FOR_ALL_ITEMS_FROM(Waypoint, waypoint_index, var, start)
#define FOR_ALL_WAYPOINTS(var) FOR_ALL_WAYPOINTS_FROM(var, 0)


/**
 * Fetch a waypoint by tile
 * @param tile Tile of waypoint
 * @return Waypoint
 */
static inline Waypoint *GetWaypointByTile(TileIndex tile)
{
	assert(IsRailWaypointTile(tile));
	return Waypoint::Get(GetWaypointIndex(tile));
}

CommandCost RemoveTrainWaypoint(TileIndex tile, DoCommandFlag flags, bool justremove);
Station *ComposeWaypointStation(TileIndex tile);
void ShowWaypointWindow(const Waypoint *wp);
void DrawWaypointSprite(int x, int y, int stat_id, RailType railtype);
void UpdateAllWaypointVirtCoords();

#endif /* WAYPOINT_H */
