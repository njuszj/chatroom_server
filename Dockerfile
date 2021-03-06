FROM  sshd:lastest
ADD server_app.sh /root/server_app.sh
RUN chmod 755 /root/server_app.sh
EXPOSE 9999
EXPOSE 10000
EXPOSE 10001
CMD ["/root/server_app.sh"]
