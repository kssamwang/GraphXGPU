cd ../build/bin
nohup ./srv_UtilServerTest_LabelPropagation 400 500 1 0 > srv1.txt 2>&1 &
nohup ./srv_UtilServerTest_LabelPropagation 400 500 1 1 > srv2.txt 2>&1 &
nohup ./srv_UtilServerTest_LabelPropagation 400 500 1 2 > srv3.txt 2>&1 &
nohup ./srv_UtilServerTest_LabelPropagation 400 500 1 3 > srv4.txt 2>&1 &
