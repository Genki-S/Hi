class Api::V1::UsersController < Api::V1::ApplicationController
  protect_from_forgery with: :null_session
  before_action :cors_set_access_control_headers

  def index
    @users = User.all
    render json: @users, status: :ok
  end

  def show
    @user = User.find(params[:id])
    render json: @user, status: :ok
  end

  def create
    new_user = false
    @user = User.find_by(uid: user_params['uid'])
    unless @user
      @user = User.new(user_params.merge({
        provider: 'facebook'
      }))
      new_user = true
    end
    if @user.save
      Message.generate_default_messages_for(@user) if new_user
      render text: 'user successfully created.', status: :created
    else
      render json: @user.errors, status: :unprocessable_entity
    end
  end

  private
    def user_params
      params.require(:user).permit(:uid, :name)
    end
end
