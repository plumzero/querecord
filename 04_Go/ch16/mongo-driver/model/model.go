
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

// upsert 测试
type PersonalInfo struct {
	Name	string 	`bson:"name"`
	Gender	string	`bson:"gender"`
	Age		int		`bson:"age"`
	Email	string	`bson:"email"`
	Status	bool	`bson:"status"`
}
