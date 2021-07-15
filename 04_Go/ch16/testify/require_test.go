package main

import (
  "testing"
  "github.com/stretchr/testify/require"
)

func TestSomething(t *testing.T) {

	// 全局 assert
	{
		// assert equality
		require.Equal(t, 123, 123, "they should be equal")

		// assert inequality
		require.NotEqual(t, 123, 456, "they should not be equal")

		// assert for nil (good for errors)
		var pi *int32 = nil
		require.Nil(t, pi)
	}

	// assert 对象
	{
		art := require.New(t)

		// assert equality
		art.Equal(123, 123, "they should be equal")
	
		// assert inequality
		art.NotEqual(123, 456, "they should not be equal")
	}
}
