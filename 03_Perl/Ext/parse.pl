
#!/usr/bin/env perl -w

# ARGV[0]: file

$args_cnt = @ARGV;
if ($args_cnt != 1) {
    print "parameter error: ./exe <file>";
    return ;
}

my $file_name = $ARGV[0];

my $digital_bag = "digital_bag";
my $yaml_config = "yam_config";
my $pcap_file = "adp_cdp.pcap";
my $algdata = "AlgData.rosbag";
my $A_VCANData_csv = "A-VCANData.csv";
my $CameraData_Front1M_264 = "CameraData_Front1M.264";
my $CameraData_Front1M_txt = "CameraData_Front1M.txt";
my $CameraData_Left1M_264 = "CameraData_Left1M.264";
my $CameraData_Left1M_txt = "CameraData_Left1M.txt";
my $CameraData_Rear1M_264 = "CameraData_Rear1M.264";
my $CameraData_Rear1M_txt = "CameraData_Rear1M.txt";
my $CameraData_Right1M_264 = "CameraData_Right1M.264";
my $CameraData_Right1M_txt = "CameraData_Right1M.txt";
my $CameraData_FL2M_264 = "CameraData_FL2M.264";
my $CameraData_FL2M_txt = "CameraData_FL2M.txt";
my $CameraData_FR2M_264 = "CameraData_FR2M.264";
my $CameraData_FR2M_txt = "CameraData_FR2M.txt";
my $CameraData_RL2M_264 = "CameraData_RL2M.264";
my $CameraData_RL2M_txt = "CameraData_RL2M.txt";
my $CameraData_RR2M_264 = "CameraData_RR2M.264";
my $CameraData_RR2M_txt = "CameraData_RR2M.txt";
my $CameraData_FL8M_264 = "CameraData_FL8M.264";
my $CameraData_FL8M_txt = "CameraData_FL8M.txt";
my $CameraData_FR8M_264 = "CameraData_FR8M.264";
my $CameraData_FR8M_txt = "CameraData_FR8M.txt";
my $CameraData_R8M_264 = "CameraData_R8M.264";
my $CameraData_R8M_txt = "CameraData_R8M.txt";
my $MobileyeData_TruthData_csv = "MobileyeData_TruthData.csv";
my $RadarData_FL_csv = "RadarData_FL.csv";
my $RadarData_FR_csv = "RadarData_FR.csv";
my $RadarData_Front_csv = "RadarData_Front.csv";
my $RadarData_RL_csv = "RadarData_RL.csv";
my $RadarData_RR_csv = "RadarData_RR.csv";
my $Tag_csv = "Tag.csv";

sub return_m {
    if ($_[1] =~ /G/) {
        return $_[0] * 1024;
    } elsif ($_[1] =~ /M/) {
        return $_[0];
    } elsif ($_[1] =~ //) {
        return $_[0] / 1024;
    }

    return 0;
}

### parse from log file
open(DATA, "<$file_name") or die "open $file_name failed: $!\n";
while (<DATA>) {
    if (/\[4\.0K\]\s+[\d]{6}_[\d]{1}/) {
        # print $_;
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z])\]\s+[\d]{4}-[\d]{2}-[\d]{2}-[\d]{2}-[\d]{2}-[\d]{2}\.bag/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+record_config\.yaml/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+adp_cdp\.pcap/) {
        print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+AlgData\.rosbag/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+PBOX_./) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+A-VCANData\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FL2M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
        # print "==========> return = ", &return_m($+{quan}, $+{unit}), "\n";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FL2M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FL8M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FL8M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FR2M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FR2M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FR8M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_FR8M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Front1M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Front1M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Left1M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Left1M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_R8M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_R8M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Rear1M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Rear1M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Right1M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_Right1M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_RL2M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_RL2M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_RR2M\.264/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+CameraData_RR2M\.txt/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+MobileyeData_TruthData\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+RadarData_FL\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+RadarData_FR\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+RadarData_Front\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+RadarData_RL\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+RadarData_RR\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    } elsif (/\[\s*(?<quan>\d*\.*\d*)(?<unit>[A-Z]|)\]\s+Tag\.csv/) {
        # print "quan=$+{quan}, unit=$+{unit}   || $_";
    }
}
close(DATA);
