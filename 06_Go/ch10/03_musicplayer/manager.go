
package library

import "errors"

type MusicManager struct {
	musics []MusicEntry
}

func NewMusicManager() * MusicManager {
	return &MusicManager{make([]MusicEntry, 0)}
}

func (m * MusicManager) Len() int {
	return len(m.musics)
}

