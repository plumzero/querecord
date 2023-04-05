
#!/usr/bin/env perl -w

use Stat;
use Util;

package StatUtil;

## 提供三个入参
## 1: 统计目标所在路径
## 2: 统计内容写入的文件
## 3: 0 或 !0, 0 表示不加头，否则表示加头
sub stat_period
{
  my $dir_path = $_[0];

  my $bag_file = $dir_path . "/AlgData/AlgData.rosbag";
  my $bag_cmd = "/path/to/bag_info";

  my $front1m_txt = $dir_path . "/CameraData_Front1M.txt";
  my $left1m_txt = $dir_path . "/CameraData_Left1M.txt";
  my $rear1m_txt = $dir_path . "/CameraData_Rear1M.txt";
  my $right1m_txt = $dir_path . "/CameraData_Right1M.txt";

  my $front1m_264 = $dir_path . "/CameraData_Front1M.264";
  my $left1m_264 = $dir_path . "/CameraData_Left1M.264";
  my $rear1m_264 = $dir_path . "/CameraData_Rear1M.264";
  my $right1m_264 = $dir_path . "/CameraData_Right1M.264";

  my $stat = new Stat();

  my $last_pos = rindex($dir_path, "/");
  $stat->set_period_name(substr($dir_path, $last_pos + 1));

  ## rosbag
  if (-e $bag_file) {
    my $cmd_bag_info = sprintf "%s --bag-name=%s", $bag_cmd, $bag_file;
    foreach (`$cmd_bag_info`) {
      if (/duration:\s+(?<duration>[\d:]+)/) {
        $stat->set_bag_duration($+{duration});
      } elsif (/start:\s+(?<start>[\d-:\s]+)\(/) {
        $stat->set_bag_start($+{start});
      } elsif (/end:\s+(?<end>[\d-:\s]+)\(/) {
        $stat->set_bag_end($+{end});
      } elsif (/size:\s+.*\((?<size>[\d\.]+)/) {
        $stat->set_bag_size($+{size});
      } elsif (/messages:\s+(?<messages>[\d]+)/) {
        $stat->set_bag_messages($+{messages});
      } elsif (/topics:\s+(?<topics>[\d]+)/) {
        $stat->set_bag_topics($+{topics});
      }
    }
  }

  ## 1m
  $stat->set_cam_front1m_size(Util::file_size($front1m_264));
  $stat->set_cam_front1m_frames(Util::frame_count($front1m_txt));

  $stat->set_cam_left1m_size(Util::file_size($left1m_264));
  $stat->set_cam_left1m_frames(Util::frame_count($left1m_txt));

  $stat->set_cam_rear1m_size(Util::file_size($rear1m_264));
  $stat->set_cam_rear1m_frames(Util::frame_count($rear1m_txt));

  $stat->set_cam_right1m_size(Util::file_size($right1m_264));
  $stat->set_cam_right1m_frames(Util::frame_count($right1m_txt));

  ## composition
  my $content = Util::join_fields(
    $stat->get_period_name(),
    $stat->get_bag_size(),
    $stat->get_bag_duration(),
    $stat->get_bag_topics(),
    $stat->get_bag_messages(),
    $stat->get_bag_duration() != "" ? "否" : "是",
    sprintf("%s/%s/%s/%s", $stat->get_cam_front1m_size(), $stat->get_cam_left1m_size(), $stat->get_cam_rear1m_size(), $stat->get_cam_right1m_size()),
    sprintf("%s/%s/%s/%s", $stat->get_cam_front1m_frames(), $stat->get_cam_left1m_frames(), $stat->get_cam_rear1m_frames(), $stat->get_cam_right1m_frames()),
    );

  # write to file
  open(DATA, ">>$_[1]") or die "open $_[1] failed: $!\n";
  if ($_[2]) {
    my $header = "|周期名称|bag大小|bag时长|topic数目|topic数量|包损坏|1M大小(前左后右)|1M帧数(前左后右)|";
    print DATA $header, "\n";
    print DATA Util::join_sperators($header), "\n";
  }
  print DATA $content, "\n";
  close(DATA);
}

1
