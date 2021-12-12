
package model

type ExecTime struct {
	StartTime int64		`bson:"startTime"`
	EndTime   int64 	`bson:"endTime"`
}

type LogRecord struct {
	JobName string `bson:"jobName"`
	Command string `bson:"command"`
	Err		string `bson:"err"`
	Content string `bson:"content"`
	Tp		ExecTime
}

type FindByJobName struct {
	JobName string `bson:"jobName"`
}