require 'sinatra'
require 'sinatra/cross_origin'

enable :cross_origin
set :public_folder, File.dirname(__FILE__)

set :bind, '0.0.0.0'
set :port, '80'

get '/' do

end

get '/screw/on' do
  cross_origin
  p 'Access: /screw/on'
  '<h1>SCREW ON</h1>'
end

get '/screw/off' do
  cross_origin
  p 'Access: /screw/off'
  '<h1>SCREW OFF</h1>'
end

get '/rudder/yaw' do
  cross_origin
  p "Access: /rudder/yaw with value=#{params['value']}"
  '<h1>RUDDER</h1>'
end
