FROM debian:bullseye
ARG USERNAME=user
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG ADDITIONAL_GID=1001


# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && groupadd --gid $ADDITIONAL_GID additional \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -G additional \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo procps
    #&& echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    #&& chmod 0440 /etc/sudoers.d/$USERNAME

# ********************************************************
# * Anything else you want to do like clean up goes here *
# ********************************************************

COPY sekrit.txt mycat attack.sh /home/$USERNAME/
RUN chown 0:1000 /home/$USERNAME/sekrit.txt && chmod 606 /home/$USERNAME/sekrit.txt

USER $USERNAME
ENTRYPOINT ["sh"]

#ENTRYPOINT ["su", "-", "user"]
