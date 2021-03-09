kubectl taint nodes --all node-role.kubernetes.io/master-
kubectl create -f server_deployment.yaml
